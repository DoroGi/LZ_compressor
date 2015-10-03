A simple LZ78 and LZW compressor.

With this, it should be possible to elaborate all kinds of file.
Keep in mind that, being a lossless compressor, it is not able to reduce ALL files.
We suggest the compression of files with low entropy such as textfiles or ".bmp".
Files with high entropy such as archives or jpeg will probably be enlarged.

It is at an early stage of development.
During the programming, the focus was on the compression ration in spite of compression speed.
In terms of compression ratio, this algorithm has the same results of Linux "compress".
It terms of compression speed, it is way slower.
In a future update this problem should be fixed.
