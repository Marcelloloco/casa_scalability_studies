# Test without paralization for tast tclean in ext4 system
/home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_tclean/casa6_data_tclean_cube.py

# Paralization test for tast tclean in ext4 system
/home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/mpicasa -n 4 /home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_tclean/casa6_data_tclean_cube_parallel.py 

/home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/mpicasa -n 8 /home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_tclean/casa6_data_tclean_cube_parallel.py

/home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/mpicasa -n 16 /home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_tclean/casa6_data_tclean_cube_parallel.py

/home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/mpicasa -n 32 /home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_tclean/casa6_data_tclean_cube_parallel.py

# Test without paralization for task tclean in LFS
/home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_tclean/casa6_fam_tclean_cube.py

# Paralization test for tast tclean in LFS system
/home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/mpicasa -n 4 /home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_tclean/casa6_fam_tclean_cube_parallel.py

/home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/mpicasa -n 8 /home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_tclean/casa6_fam_tclean_cube_parallel.py

/home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/mpicasa -n 16 /home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_tclean/casa6_fam_tclean_cube_parallel.py

/home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/mpicasa -n 32 /home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_tclean/casa6_fam_tclean_cube_parallel.py

echo Results from DATA:
cat casa6_data_tclean_500_0-13_cube.log | grep complete_time

echo Results from LFS:
cat casa6_fam_tclean_500_0-13_cube.log | grep complete_time