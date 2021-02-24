
.. index::
	single: how_stream_capture_works

How the stream capture is implemented
=======================================

The three standard streams `stdout <https://linux.die.net/man/3/stdout>`_, 
`stderr <https://linux.die.net/man/3/stderr>`_ and `stdin <https://man7.org/linux/man-pages/man3/stdin.3.html>`_ are basically `FILE` handles 
that have specific behaviours, writing to any of these stream is same as writing to a file opened 
with the function `fopen <https://linux.die.net/man/3/fopen>`_.

When a stream is captured in in libcester a new temporary text file with the name as the address of that stream 
is created in a temporary folder. The temporary folder varies across various operating systems, the default 
location on windows is determined by the return value of `getenv("TEMP")` if not set the folder 
`"C:/libcester_tmp/"` is used. On other platforms the value of `getenv("TMPDIR")` is used and if not set 
the fallback folder is `"/tmp/libcester_tmp/"`.

At the point of capture the stream variable is updated to point to the stream address of the new text file 
created in the temporary folder, the actual address of the stream is cached in the stream_capture_object and at 
the point of stream release the created file is closed and deleted and the stream variable is updated to point 
to the original stream address cached in the stream_capture_object.

The file is opened with the the create + write mode **w+**, on reset the file handle is closed and reopened 
with the **w+** mode. The handle is kept open until the stream is released, so it important to always release 
captured streams.
