-- These have the same type
a = ("Porpoise", "Grey")
b = ("Table", "Oak")

{-
 - even though these seem to have the same definition
 - (except for the constructor name) the are different
 - types.
-}

data Cetacean = Cetacean String String
data Furniture = Furniture String String

c = Cetacean "Porpoise" "Grey"
d = Furniture "Table" "Oak"
