{-# LANGUAGE Arrows #-}
module Main where

import Control.Concurrent
import Data.IORef

import FRP.Yampa
import Graphics.UI.GLUT hiding (Level, Vector3(..),normalize)

import Lib

fallingBall :: Pos -> Vel -> SF () (Pos, Vel)
fallingBall y0 v0 = proc input -> do
    v <- integral >>^ (+ v0) -< -9.81
    y <- integral >>^ (+ y0) -< v
    returnA -< (y, v)

bouncingBall :: Pos -> Vel -> SF () (Pos, Vel)
bouncingBall y0 v0 = switch (bb y0 v0) (\ (pos, vel) -> if abs vel <= 1 then constant (0,0) else bouncingBall pos ((-vel) * 0.6))
    where bb y0' v0' = proc input -> do
                            (pos, vel) <- fallingBall y0' v0' -< input 
                            event <- edge -< pos <= 0
                            returnA -< ((pos, vel), event `tag` (pos, vel))

main :: IO ()
main = do
    oldTime <- newIORef (0 :: Int)
    rh <- reactInit (initGL) (\_ _ b -> b >> return False)
                    mainSF
    displayCallback $= return ()
    idleCallback $= Just (idle oldTime rh)
    oldTime' <- get elapsedTime
    writeIORef oldTime oldTime'
    mainLoop

mainSF = (bouncingBall 10.0 0.0) >>^ (\ (pos, vel) -> putStrLn ("pos: " ++ show pos ++ ", vel: " ++ show vel) >> draw pos)
