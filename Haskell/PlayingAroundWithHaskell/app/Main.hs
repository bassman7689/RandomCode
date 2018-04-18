module Main where

import Lib
import Control.Monad

{- half x = if even x then Just (x `div` 2) else Nothing

main :: IO ()
main = do
    let a = push 1 Empty
    let b = push 2 a
    let (x, c) = pop b
    putStrLn $ show a
    putStrLn $ show b
    putStrLn $ show x
    putStrLn $ show c -}

type Birds = Int

type Pole = (Birds, Birds)

landLeft :: Birds -> Pole -> Maybe Pole
landLeft n (left, right)
    | abs ((left + n) - right) < 4 = Just (left + n, right)
    | otherwise                   = Nothing

landRight :: Birds -> Pole -> Maybe Pole
landRight n (left, right)
    | abs (left - (right + n)) < 4 = Just (left, right + n)
    | otherwise                   = Nothing

banana :: Pole -> Maybe Pole
banana _ = Nothing

foo :: Maybe String
foo = do
    x <- Just 3
    y <- Just "!"
    return (show x ++ y)

routine :: Maybe Pole
routine = do
    start <- return (0, 0)
    first <- landLeft 2 start
    Nothing
    second <- landRight 2 first
    landLeft 1 second

justH :: Maybe Char
justH = do
    (x:xs) <- Just "hello"
    return x

wopwop :: Maybe Char
wopwop = do
    (x:xs) <- Just ""
    return x

type KnightPos = (Int, Int)

moveKnight :: KnightPos -> [KnightPos]
moveKnight (c,r) = do
    (c',r') <- [(c+2, r-1), (c+2, r+1), (c-2, r-1), (c-2, r+1)
               ,(c+1, r-2), (c+1, r+2), (c-1, r-2), (c-1, r+2)
               ]
    guard (c' `elem` [1..8] && r' `elem` [1..8])
    return (c', r')

in3 :: KnightPos -> [KnightPos]
in3 start = return start >>= moveKnight >>= moveKnight >>= moveKnight

canReachIn3 :: KnightPos -> KnightPos -> Bool
canReachIn3 start end = end `elem` in3 start

main = do
    putStrLn . show $ (6, 2) `canReachIn3` (6, 1)
    putStrLn . show $ (6, 2) `canReachIn3` (7, 3)
