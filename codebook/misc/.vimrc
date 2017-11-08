syntax on
set nocp
set rnu nu
set ts=2 sts=2 sw=2
set ai si et sta
set cul is ls=2
set mouse=a

set makeprg=g++\ -std=c++14\ -g\ -Wall\ -Wextra\ -fsanitize=undefined,address\ %\ -o\ %:r
command -nargs=* Make make <args> | cwindow
nnoremap <buffer> <F4> :Make<CR>
nnoremap <buffer> <F5> :!./%:r<CR>

nnoremap <buffer> ]q :cn<CR>
nnoremap <buffer> [q :cp<CR>
