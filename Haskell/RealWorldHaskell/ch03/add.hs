myNot True = False
myNot False = True

sumList :: Num a => [a] -> a
sumList list = sumList' 0 list
    where sumList' :: Num a => a -> [a] -> a
          sumList' n [] = n
          sumList' n (x:xs) = sumList' (n + x) xs
