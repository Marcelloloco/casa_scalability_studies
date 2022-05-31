# Test without paralization for split cleaning task in ext4 system
/home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_split/casa5_data_split_NOT_PARA.py

# Paralization test for split cleaning task in ext4 system
/home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/mpicasa -n 4 /home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_split/casa5_data_split_PARA.py

/home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/mpicasa -n 8 /home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_split/casa5_data_split_PARA.py

/home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/mpicasa -n 16 /home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_split/casa5_data_split_PARA.py

/home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/mpicasa -n 32 /home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_split/casa5_data_split_PARA.py


# Test without paralization for split cleaning task in LFS
/home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_split/casa5_fam_split_NOT_PARA.py

# Paralization test for split cleaning task in LFS
/home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/mpicasa -n 4 /home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_split/casa5_fam_split_PARA.py

/home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/mpicasa -n 8 /home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_split/casa5_fam_split_PARA.py

/home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/mpicasa -n 16 /home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_split/casa5_fam_split_PARA.py

/home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/mpicasa -n 32 /home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_split/casa5_fam_split_PARA.py


# Echo results from log files
echo echo Results from DATA not parallel:
cat casa5_data_clean_split_10000_0-13_mosaic_not_parallel.log | grep !

echo echo Results from DATA parallel:
cat casa5_data_clean_split_10000_0-13_mosaic_parallel.log | grep !

echo Results from LFS not parallel:
cat casa5_fam_clean_split_10000_0-13_mosaic_not_parallel.log | grep !

echo Results from LFS not parallel:
cat casa5_fam_clean_split_10000_0-13_mosaic_parallel.log | grep !