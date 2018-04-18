safeHead :: [a] -> Maybe a
safeHead [] = Nothing
safeHead (x:xs) = Just x

safeTail :: [a] -> Maybe [a]
safeTail [] = Nothing
safeTail (x:xs) = Just xs

safeLast :: [a] -> Maybe a
safeLast [] = Nothing
safeLast [x] = Just x
safeLast (x:xs) = safeLast xs

-- this safe init uses less memory
safeInit :: [a] -> Maybe [a]
safeInit [] = Nothing
safeInit xs = safeInit' [] xs
    where safeInit' :: [a] -> [a] -> Maybe [a]
          safeInit' xs [y] = Just (reverse xs)
          safeInit' xs (y:ys) = safeInit' (y:xs) ys

{-
 - this safe init uses more memory
 - and is slower but doesn't need
 - a reverse
 -}
safeInitSlow :: [a] -> Maybe [a]
safeInitSlow [] = Nothing
safeInitSlow xs = safeInit' [] xs
    where safeInit' :: [a] -> [a] -> Maybe [a]
          safeInit' xs [y] = Just xs
          safeInit' xs (y:ys) = safeInit' (xs ++ [y]) ys
