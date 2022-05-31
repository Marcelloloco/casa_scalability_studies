# Test without paralization for tast tclean in ext4 system
/home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_tclean/casa5_data_tclean_NO_PARA.py

# Paralization test for tast tclean in ext4 system
/home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/mpicasa -n 4 /home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_tclean/casa5_data_tclean_PARA.py 

/home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/mpicasa -n 8 /home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_tclean/casa5_data_tclean_PARA.py

/home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/mpicasa -n 16 /home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_tclean/casa5_data_tclean_PARA.py

/home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/mpicasa -n 32 /home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_tclean/casa5_data_tclean_PARA.py

# Test without paralization for task tclean in LFS
/home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_tclean/casa5_fam_tclean_NO_PARA.py

# Paralization test for tast tclean in LFS system
/home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/mpicasa -n 4 /home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_tclean/casa5_fam_tclean_PARA.py

/home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/mpicasa -n 8 /home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_tclean/casa5_fam_tclean_PARA.py

/home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/mpicasa -n 16 /home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_tclean/casa5_fam_tclean_PARA.py

/home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/mpicasa -n 32 /home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_tclean/casa5_fam_tclean_PARA.py

echo Results from DATA:
cat casa5_data_tclean_500_0-13_mosaic.log | grep complete_time

echo Results from LFS:
cat casa5_fam_tclean_500_0-13_mosaic_mfs.log | grep complete_time