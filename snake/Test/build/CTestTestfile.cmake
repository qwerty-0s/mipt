# CMake generated Testfile for 
# Source directory: /home/au/C/mipt/mipt/snake/Test
# Build directory: /home/au/C/mipt/mipt/snake/Test/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(SnakeTests "/home/au/C/mipt/mipt/snake/Test/build/snake_tests")
set_tests_properties(SnakeTests PROPERTIES  _BACKTRACE_TRIPLES "/home/au/C/mipt/mipt/snake/Test/CMakeLists.txt;50;add_test;/home/au/C/mipt/mipt/snake/Test/CMakeLists.txt;0;")
subdirs("_deps/googletest-build")
