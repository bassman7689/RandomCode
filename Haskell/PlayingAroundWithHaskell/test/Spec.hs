import Test.HUnit

import Lib

testIncrNum :: (Num a, Eq a, Show a) => [a] -> Test
testIncrNum dataSet = test $ map createTest dataSet
    where
    createTest num = TestLabel (name num) (testFunction num)
    testFunction num = TestCase $ assertEqual ("for " ++ (name num)) (num + 1) (incrNum num)
    name num = "incrNum " ++ (show num)

testTestFunc = TestCase $ assertEqual "1 equals 1" 1 1

tests = test [
	  TestLabel "assert 1 equals 1" testTestFunc
	, testIncrNum [1..100]
        ]


main :: IO Counts
main = runTestTT tests
