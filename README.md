# mnist

Extracting images from the [MNIST Database of handwritten digits][mnist].

[mnist]: http://yann.lecun.com/exdb/mnist/index.html

## Sample output

    $ tcc extract.c
    $ ./a.out 
    magic number: 0x00000801(2049)
    number of items: 60000
    magic number: 0x00000803(2051)
    number of images: 60000
    number of rows: 28
    number of cols: 28
    ...
    $ ls imgs
    1-5.pgm
    10-4.pgm
    100-1.pgm
    1000-6.pgm
    10000-7.pgm
    10001-3.pgm
    10002-8.pgm
    10003-7.pgm
    10004-9.pgm
    10005-9.pgm
    10006-0.pgm
    10007-1.pgm
    10008-1.pgm
    10009-5.pgm
    ...
    
