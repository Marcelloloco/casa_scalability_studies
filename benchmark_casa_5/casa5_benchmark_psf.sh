# Test without paralization for task psf in ext4 system
/home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_psf/casa5_data_psf_NOT_PARA.py

# Paralization test for task psf in ext4 system
/home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/mpicasa -n 4 /home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_psf/casa5_data_psf_PARA.py

/home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/mpicasa -n 8 /home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_psf/casa5_data_psf_PARA.py

/home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/mpicasa -n 16 /home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_psf/casa5_data_psf_PARA.py

/home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/mpicasa -n 32 /home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_psf/casa5_data_psf_PARA.py


# Test without paralization for task psf in LFS
/home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_psf/casa5_fam_psf_NOT_PARA.py

# Paralization test for tast pfs in LFS system
/home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/mpicasa -n 4 /home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_psf/casa5_fam_psf_PARA.py

/home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/mpicasa -n 8 /home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_psf/casa5_fam_psf_PARA.py

/home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/mpicasa -n 16 /home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_psf/casa5_fam_psf_PARA.py

/home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/mpicasa -n 32 /home/mtrattner/casa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/mtrattner/casa/benchmark/task_psf/casa5_fam_psf_PARA.py


# Echo results from log files
echo echo Results from DATA not parallel:
cat casa5_data_pysynthesisimager_clean_500_0-13_mosaic_psfonly_notparall.log | grep MakePSF

echo echo Results from DATA parallel:
cat casa5_data_pysynthesisimager_clean_500_0-13_mosaic_psfonly_parall.log | grep MakePSF

echo Results from LFS not parallel:
cat casa5_fam_pysynthesisimager_clean_500_0-13_mosaic_psfonly_notparall.log | grep MakePSF

echo Results from LFS not parallel:
cat casa5_fam_pysynthesisimager_clean_500_0-13_mosaic_psfonly_parall.log | grep MakePSF