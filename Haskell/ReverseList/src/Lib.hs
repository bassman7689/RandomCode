module Lib
    ( someFunc,
      reverseList
    ) where

someFunc :: IO ()
someFunc = putStrLn "someFunc"

reverseList :: [a] -> [a]
reverseList [] = []
reverseList (x:xs) = reverseList xs ++ [x]
