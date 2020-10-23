
.. toctree::
   :hidden:
   :maxdepth: 1
   :caption: Main
   :name: main-nav

   /download
   /faq
   /screenshots


.. toctree::
   :hidden:
   :glob:
   :maxdepth: 1
   :caption: Documentation
   :name: docs-nav

   /docs/*


.. toctree::
   :hidden:
   :glob:
   :maxdepth: 1
   :caption: How it works
   :name: docs-how_it_works

   /how_it_works/*

.. raw:: html

    <style>
        .documentwrapper {
            margin: 0px;
            margin-top: 550px;
        }
        .bodywrapper {
            margin-left: 15%;
            width:70%;
        }
    </style>
    <div class="header">
        <div class="overlay">
            <img src="_static/libcester.png" alt="libcester logo"><br/><br/>
            <span class="title">libcester</span><br/>
            <p class="brief">
                A robust header only unit testing framework for C and C++ programming language. <br/>
                Support function mocking, memory leak detection, crash report. Works on various 
                platorms including embedded <br/>systems and compatible with various compilers. Requires 
                no dependency only the header file is needed to get the tests running.

                <div class="linksdiv">
                    <a class="link" href="./download.html">Download</a>
                    <a class="link" href="./docs/">Documentation</a>
                    <a class="link" href="./reference/">API Reference</a>
                </div>
            </p>
        </div>
    </div>

    <div class="features-flex">
        <div class="project main-project" style="display: block;">
            <span class="title">Write Once, Test Anywhere</span><br>
            <p class="description">
                libcester is compliant with the original C language specification 
                ISO/IEC 9899:1990 and the first POSIX specification IEEE Std 1003.1-1988 
                which ensures the project compatibility in various environments including 
                embedded systems.<br/><br/>
                
                It also makes use of features in the newer revisions ISO/IEC 9899:1999 
                and IEEE Std 1003.1-2001 whenever possible.
            </p>
        </div>
        <div class="project main-project" style="display: block;">
            <span class="title">Automatic Tests Registration</span><br>
            <p class="description">
                With the stretched use of C preprocessor libcester in most cases does not 
                require you to manually register your test cases, you just define your test with 
                the provided macros and it will be executed.
            </p>
        </div>
        <div class="project main-project" style="display: block;">
            <span class="title">Supports various output formats</span><br>
            <p class="description">
                libcester supports various output formats for test analysis. The following output 
                formats are supported:
                
                <ul>
                    <li><a href="./docs/output_formats.html#text">Text</a></li>
                    <li><a href="./docs/output_formats.html#junitxml">JunitXML</a></li>
                    <!--<li><a href="./docs/output_formats.html#xunitxml">xUnitXML</a></li>
                    <li><a href="./docs/output_formats.html#xunitxml">Subunit</a></li>
                    <li><a href="./docs/output_formats.html#key-value-log">Key Value log</a></li>-->
                    <li><a href="./docs/output_formats.html#tap">Test Anything Protocol</a></li>
                    <li><a href="./docs/output_formats.html#tap-version-13">Test Anything Protocol Version 13</a></li>
                </ul> 
            </p>
        </div>
        <div class="project main-project" style="display: block;">
            <span class="title">Detailed documentation</span><br>
            <p class="description">
                The <a class="link" href="./docs/">documentation</a> provides several examples, 
                tutorials, and detailed guides for using the library. <br/><br/>

                While <a class="link" href="./reference/">reference</a> provides a 
                low-level overview of all the implemented APIs in the library
            </p>
        </div>
        <div class="project main-project" style="display: block;">
            <span class="title">Function mocking</span><br>
            <p class="description">
                Create functions that simulate the behaviour of the real function implementation. 
                <br/><br/>
                Mocking function is useful when your unit tests relies on dependencies which are 
                not available at the time of running your tests.
            </p>
        </div>
        <div class="project main-project" style="display: block;">
            <span class="title">Isolated unit testing</span><br>
            <p class="description">
                Each test case is run in isolation which allows exceptions like a segfault, 
                premature termination e.t.c to be reported. <br/><br/>
                
                A crahsed test case does not cause the testing to stop instead the test case is 
                reported as failure and libcester continue running other test cases.
            </p>
        </div>
        <div class="project main-project" style="display: block;">
            <span class="title">Shared objects</span><br>
            <p class="description">
                Each test cases accepts a <a class="link" href="reference/structtest__instance.html">test_instance</a> 
                variable that can be used to share data across multiple test cases.<br/><br/>

                There are also CESTER_BEFORE_ALL, CESTER_BEFORE_EACH, CESTER_AFTER_EACH and 
                CESTER_AFTER_ALL macros to setup and tear down shared functions and objects use 
                in the test cases.
            </p>
        </div>
        <div class="project main-project" style="display: block;">
            <span class="title">Testing of memory leaks</span><br>
            <p class="description">
                The library detects memory leak in the test cases without the need to run 
                program like valgrind. The precise amount of bytes leaked is reported for 
                each test case.<br/><br/>

                Memory leak test is optional and can be diabled with the option 
                <span class="bold">--cester-nomemtest</span>
            </p>
        </div>
        <div class="project main-project" style="display: block;">
            <span class="title">MIT License</span><br>
            <p class="description">
                This allows you to use the library freely in your open or closed source project. 
                You also have the freedom to modify your version so far it provides the freedom 
                MIT License stated.
            </p>
        </div>
    </div>

    <div class="two-sided">
        <div class="left-side">
            <h3 class="title">Intuitive APIs</h3>
            <br/>

            Cester provides clean macros to write your unit tests. You don't have to worry about 
            test case registration it all taken care of at compile time. Optionally you can 
            manually register specific test cases.

            <br/><br/>
            There are various <a href="./docs/assertions.html">assertion macros</a>
            available for use in your test. 
        </div>
        <div class="right-side">
            <div class="highlight-c notranslate"><div class="highlight"><pre>
    #include &lt;exotic/cester.h>

    CESTER_BEFORE_ALL(test_instance, 
        test_instance->arg = (void*) "exoticlibs";
    )

    CESTER_TEST(test_assert_cmp_msg, test_instance, 
        cester_assert_cmp_msg(NULL, ==, ((void*)0), "Check if NULL is same as ((void*)0)");
        cester_assert_cmp_msg(NULL, !=, "String", "is NULL equal to 'String'");
    )

    CESTER_TEST(test_string, test_instance, 
        cester_assert_str_equal((char*)test_instance->arg, "exoticlibs");
        cester_assert_str_not_equal((char*)test_instance->arg, NULL);
    )</pre></div>
            </div>
        </div>
    </div>

