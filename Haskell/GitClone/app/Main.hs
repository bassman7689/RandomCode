{-# LANGUAGE OverloadedStrings, ScopedTypeVariables, BangPatterns, RecordWildCards #-}
module Main where

import Lib
import qualified Data.ByteString.Char8 as C
import qualified Data.ByteString as B
import qualified Data.ByteString.Lazy as L
import Network.Socket hiding (recv, send)
import Network.Socket.Internal (withSocketsDo)
import Network.Socket.ByteString (recv, sendAll)
import Data.Monoid (mempty, mappend)
import Data.Maybe (fromMaybe)
import Text.Printf (printf)
import Numeric (readHex)

withConnection :: HostName -> ServiceName -> (Socket -> IO b) -> IO b
withConnection host port consumer = do
    sock <- openConnection host port
    r <- consumer sock
    close sock
    return r

send :: Socket -> String -> IO ()
send sock msg = sendAll sock $ C.pack msg

receive :: Socket -> IO C.ByteString
receive sock = receive' sock mempty
    where receive' s acc = do
              maybeLine <- readPacketLine s
              maybe (return acc) (receive' s . mappend acc) maybeLine

openConnection :: HostName -> ServiceName -> IO Socket
openConnection host port = do
    addrInfos <- getAddrInfo Nothing (Just host) (Just port)
    let serverAddr = head addrInfos
    sock <- socket (addrFamily serverAddr) Stream defaultProtocol
    connect sock (addrAddress serverAddr)
    return sock

readPacketLine :: Socket -> IO (Maybe C.ByteString)
readPacketLine sock = do
    len <- readFully mempty 4
    if C.null len then return Nothing else
        case readHex $ C.unpack len of
            ((l,_):_) | l > 4 -> do
                line <- readFully mempty (l-4)
                return $ Just line
            _                 -> return Nothing

    where readFully acc expected = do
              line <- recv sock expected
              let len = C.length line
                  acc' = acc `mappend` line
                  cont = len /= expected && not (C.null line)
              if cont then readFully acc' (expected - len) else return acc'

data Remote = Remote {
    getHost       :: String
  , getPort       :: Maybe Int
  , getRepository :: String
}

type PacketLine = String

pktLine :: String -> String
pktLine msg = printf "%04x%s" (length msg) msg

flushPkt = pktLine ""

parsePacket :: L.ByteString -> String
parsePacket = C.unpack . L.toStrict 

gitProtoRequest :: String -> String -> String
gitProtoRequest host repo = pktLine $ "git-upload-pack /" ++ repo ++ "\0host="++host++"\0"

lsRemote :: Remote -> IO PacketLine
lsRemote Remote{..} = withSocketsDo $
    withConnection getHost (show $ fromMaybe 9418 getPort) $ \sock -> do
        let payload = gitProtoRequest getHost getRepository
        send sock payload
        response <- receive sock
        send sock flushPkt
        return $ parsePacket $ L.fromChunks [response]

main :: IO ()
main = do 
  response <- lsRemote Remote {getHost = "192.30.253.112", getPort=Nothing, getRepository="srodman7689/net-amazon-ec2"}
  putStr response
