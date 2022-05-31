# Test without paralization for task psf in ext4 system
/home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_psf/casa6_data_psf.py 

# Paralization test for task psf in ext4 system
/home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/mpicasa -n 4 /home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_psf/casa6_data_psf_parallel.py

/home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/mpicasa -n 8 /home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_psf/casa6_data_psf_parallel.py

/home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/mpicasa -n 16 /home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_psf/casa6_data_psf_parallel.py

/home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/mpicasa -n 32 /home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_psf/casa6_data_psf_parallel.py


# Test without paralization for task psf in LFS
/home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_psf/casa6_fam_psf.py

# Paralization test for tast pfs in LFS system
/home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/mpicasa -n 4 /home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_psf/casa6_fam_psf_parallel.py

/home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/mpicasa -n 8 /home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_psf/casa6_fam_psf_parallel.py

/home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/mpicasa -n 16 /home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_psf/casa6_fam_psf_parallel.py

/home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/mpicasa -n 32 /home/mtrattner/casa/casa-6.4.4-31-py3.6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_psf/casa6_fam_psf_parallel.py


# Echo results from log files
echo echo Results from DATA not parallel:
cat casa5_data_pysynthesisimager_clean_500_0-13_mosaic_psfonly_notparall.log | grep MakePSF

echo echo Results from DATA parallel:
cat casa5_data_pysynthesisimager_clean_500_0-13_mosaic_psfonly_parall.log | grep MakePSF

echo Results from LFS not parallel:
cat casa5_fam_pysynthesisimager_clean_500_0-13_mosaic_psfonly_notparall.log | grep MakePSF

echo Results from LFS not parallel:
cat casa5_fam_pysynthesisimager_clean_500_0-13_mosaic_psfonly_parall.log | grep MakePSF