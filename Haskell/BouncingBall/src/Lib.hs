module Lib
    ( initGL
    , draw
    , idle
    , Pos
    , Vel
    ) where

import FRP.Yampa
import FRP.Yampa.Vector3
import FRP.Yampa.Utilities
import Unsafe.Coerce
import Data.IORef

import Graphics.UI.GLUT hiding (Level, Vector3(..),normalize)
import qualified Graphics.UI.GLUT as G(Vector3(..))

type Pos = Double
type Vel = Double

type R = GLdouble


initGL :: IO ()
initGL = do
    getArgsAndInitialize

    initialWindowSize  $= Size 640 480
    initialDisplayMode $= [ WithDepthBuffer ]

    createWindow "Bounce"
    depthFunc         $= Just Less
    clearColor        $= Color4 0 0 0 0
    light (Light 0)   $= Enabled
    lighting          $= Enabled
    lightModelAmbient $= Color4 0.5 0.5 0.5 1
    diffuse (Light 0) $= Color4 1 1 1 1
    blend             $= Enabled
    blendFunc         $= (SrcAlpha, OneMinusSrcAlpha)
    colorMaterial     $= Just (FrontAndBack, AmbientAndDiffuse)
    reshapeCallback   $= Just resizeScene
    return ()

resizeScene :: Size -> IO ()
resizeScene (Size w 0) = resizeScene (Size w 1)
resizeScene s@(Size width height) = do
    viewport   $= (Position 0 0, s)
    matrixMode $= Projection
    loadIdentity
    perspective 45 (w2/h2) 1 1000
    matrixMode $= Modelview 0
    flush
    where
        w2 = half width
        h2 = half height
        half z = realToFrac z / 2

draw :: Pos -> IO ()
draw pos = do
    clear [ ColorBuffer, DepthBuffer ]
    loadIdentity
    renderPlayer $ vector3 2 (unsafeCoerce pos) (-30)
    flush
    where size2 :: R
          size2 = (fromInteger $ 6)/2
          red    = Color4 1.0 0.7 0.8 1.0 :: Color4 R
          renderShapeAt s p = preservingMatrix $ do
              translate $ G.Vector3 (0.5 - size2 + vector3X p)
                                    (0.5 - size2 + vector3Y p)
                                    (0.5 - size2 + vector3Z p)
              renderObject Solid s
          renderPlayer = (color red >>) . (renderShapeAt $ Sphere' 0.5 20 20)

idle :: IORef Int -> ReactHandle () (IO ()) -> IO ()
idle oldTime rh = do
    newTime'  <- get elapsedTime
    oldTime'  <- get oldTime
    let dt = (fromIntegral $ newTime' - oldTime')/1000
    react rh (dt, Nothing)
    writeIORef oldTime newTime'
    return()
