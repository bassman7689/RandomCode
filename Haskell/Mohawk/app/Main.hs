module Main where

import qualified Mohawk as M
import qualified System.Console.Haskeline as HL

mainLoop :: HL.InputT IO ()
mainLoop = do
  minput <- HL.getInputLine "user> "
  case minput of
    Nothing -> return ()
    Just input -> do
      HL.outputStrLn $ M.rep input
      mainLoop

main :: IO ()
main = do
  M.printHeader
  HL.runInputT HL.defaultSettings mainLoop
