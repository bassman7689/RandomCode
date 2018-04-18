module Mohawk.Types
    ( MalVal(..)
    ) where

data MalVal = List [MalVal]
            | Number Int
            | Symbol String
            | Error String
    deriving (Show)

