module Mohawk
    ( printHeader
     ,rep
    ) where

import qualified Mohawk.Read as MR
import qualified Mohawk.Types as MT
import qualified Text.Parsec.Error as TPE

version = "0.0.1"

eval :: Either TPE.ParseError MT.MalVal -> MT.MalVal
eval (Left err) = MT.Error $ show err
eval (Right val) = val

print :: MT.MalVal -> String
print (MT.Symbol x) = x
print (MT.Number x) = show x
print (MT.Error x) = x
print (MT.List x) = ('(' : list) ++ ")"
  where list = unwords $ map (Mohawk.print) x

rep :: String -> String
rep = (Mohawk.print . eval . MR.read)

printHeader = putStrLn $ "Mohawk LISP " ++ version ++ "\nPress CTRL-D to exit\n"
