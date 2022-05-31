import time
casalog.setlogfile('casa5_fam_tclean_500_0-13_mosaic_mfs.log')
casalog.filter('DEBUG2') #more details
rmtables('Antennae_North.Cont.clean.workdirectory/Antennae_North.Cont.clean.*')
rmtables('Antennae_North.Cont.clean.*')
start = time.time()
tclean(
       vis='/lfs/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/',
       imagename='Antennae_North.Cont.clean',
       field='',
       phasecenter=12,
       deconvolver='hogbom',
       specmode='mfs', # Biggest impact on performance
       restfreq='345.79599GHz',
       spw='0:1~50;120~164',
       gridder='mosaic',
       imsize=500,
       cell='0.13arcsec',
       interactive=False,
       niter=1000,
       parallel=True)# set False for not parallel)
end = time.time()
final_part = (end - start)
print(final_part)
write_f=open('casa5_fam_tclean_500_0-13_mosaic_mfs.log', 'a')
write_f.write(str("tclean_complete_time_fam: %s" % final_part))
write_f.write('\n')
write_f.close()