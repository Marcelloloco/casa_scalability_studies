import time
casalog.setlogfile('casa6_data_tclean_500_0-13_cube.log')
casalog.filter('DEBUG2') #more details
rmtables('Antennae_North.Cont.clean.workdirectory/Antennae_North.Cont.clean.*')
rmtables('Antennae_North.Cont.clean.*')
start = time.time()
tclean(
       vis='/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/',
       imagename='Antennae_North.Cont.clean',
       field='',
       phasecenter=12,
       deconvolver='hogbom',
       specmode='cube',
       restfreq='345.79599GHz',
       spw='0:1~50;120~164',
       gridder='mosaic',
       imsize=500,
       cell='0.13arcsec',
       interactive=False,
       niter=1000,
       parallel=False)#set False for no parallelization)
end = time.time()
final_part = (end - start)
print(final_part)
write_f=open('casa6_data_tclean_500_0-13_cube.log', 'a')
write_f.write(str("tclean_complete_time: %s" % final_part))
write_f.write('\n')
write_f.close()
