module Mohawk.Read
    ( Mohawk.Read.read
    ) where

import qualified Control.Applicative as  CA
import qualified Data.Functor.Identity as DFI
import qualified Mohawk.Types as MT
import qualified Text.ParserCombinators.Parsec as P
import qualified Text.Parsec.Error as TPE
import qualified Text.Parsec.Prim as TPP

read :: String -> Either TPE.ParseError MT.MalVal
read x = P.parse (parseSexpr) "mohawk" x

parseSexpr = (parseForm)

parseList = MT.List <$> '(' `parseCollection` ')'

parseCollection :: Char -> Char -> TPP.ParsecT String u DFI.Identity [MT.MalVal]
parseCollection left right =
  P.between (P.spaces *> P.char left <* P.spaces) (P.spaces *> P.char right) $ (parseForm) `P.sepBy` (P.space)

parseForm = P.try parseList P.<|> P.try parseAtom

parseAtom =  MT.Number <$> P.try parseNumber
       P.<|> MT.Symbol <$> P.try parseSymbol

parseNumber = do
  s <- P.getInput
  case reads s of
    [(n, s')] -> n <$ P.setInput s'
    _         -> CA.empty

parseSymbol = P.many1 $ P.satisfy (`notElem` " ()")
