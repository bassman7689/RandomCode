module Lib
    ( greeting
    , myFmap
    , Stack(..)
    , push
    , pop
    , top
    , size
    ) where

greeting :: [Char] -> IO ()
greeting name = putStrLn message
    where message = "Hello " ++ name ++ "!"

myFmap f action = do
    result <- action
    return (f result)

data Stack a = Empty
             | MkStack a (Stack a)
             deriving (Show)

push :: a -> Stack a -> Stack a
push x s = MkStack x s

pop :: Stack a -> (a, Stack a)
pop (MkStack x s) = (x, s)

top :: Stack a -> a
top (MkStack x s) = x

size :: Stack a -> Int
size s = size' 0 s
    where size' x Empty = x
          size' x (MkStack _ s) = size' (x+1) s
