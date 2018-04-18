set nonumber
set nofoldenable
set nocursorcolumn
set nocursorline
if exists('+relativenumber')
  set norelativenumber
end
set hidden


noremap <PageUp> :bp<CR>
noremap <Left> :bp<CR>
noremap <PageDown> :bn<CR>
noremap <Right> :bn<CR>
noremap Q :q<CR>

b 1
b 2
b 3
9,10SyntaxInclude sh
b 4
9,14SyntaxInclude grub
b 5
b 6
b 7
b 8
9,17SyntaxInclude asm
b 1
