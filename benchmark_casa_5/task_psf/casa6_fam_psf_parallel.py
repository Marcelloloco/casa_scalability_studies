##/home/elsa/casa-release-5.1.1-5.el6/bin/mpicasa -n 8 /home/elsa/casa-release-5.1.1-5.el6/bin/casa --nogui --log2term -c /home/elsa/Master_code_sandbox/schaaf/Antennae_benchmark/speedup_tests/internal_speedup/clean_image/casa5_data_pysynthesisimager_clean_majorparall.py
#todo logger, rm -rf rmtables('<imagename>.*')

## (1) Import the python application layer
import time
from casatasks.private.imagerhelpers.input_parameters import ImagerParameters
from casatasks.private.imagerhelpers.imager_parallel_continuum import PyParallelContSynthesisImager     # Step (1)


## print into defined logfile
casalog.setlogfile('casa5_fam_pysynthesisimager_clean_500_0-13_mosaic_psfonly_parall.log')

## instead of rm -rf use casa function rmtables, to rm the cached data
rmtables('Antennae_North.Cont.clean.workdirectory/Antennae_North.Cont.clean.*')
rmtables('Antennae_North.Cont.clean.*')

## (2) Set up Input Parameters
## - List all parameters that you need here
## - Defaults will be assumed for unspecified parameters
## - Nearly all parameters are identical to that in the task. Please look at the
## list of parameters under __init__ using " help ImagerParameters " )

paramList = ImagerParameters(
msname ='/lfs/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/',
      imagename='Antennae_North.Cont.clean',
      field='',
      phasecenter=12,
      specmode='mfs',
      deconvolver='hogbom',
      restfreq='345.79599GHz',
      spw='0:1~50;120~164',
      gridder='mosaic',
      imsize=500, #test 10000 ok
      cell='0.13arcsec', # test 0.13arcsec 0.2
      interactive=False,
      niter=1000)
## (3) Construct the PySynthesisImager object, with all input parameters

imager = PyParallelContSynthesisImager(params=paramList)


## (4) Initialize various modules.
## - Pick only the modules you will need later on. For example, to only make
## the PSF, there is no need for the deconvolver or iteration control modules.

## Initialize modules major cycle modules

imager.initializeImagers()
imager.initializeNormalizers()
imager.setWeighting()

## Init minor cycle modules

#imager.initializeDeconvolvers()
#imager.initializeIterationControl()

## (5) Make the initial images
print "makePSF!"
write_f=open('casa5_fam_pysynthesisimager_clean_500_0-13_mosaic_psfonly_parall.log', 'a')
write_f.write(str("MAKE PSF" ))
write_f.write('\n')
write_f.close()

start = time.time()
imager.makePSF()
end = time.time()
final_part = (end - start)
print("makePSF:", final_part)
write_f=open('casa5_fam_pysynthesisimager_clean_500_0-13_mosaic_psfonly_parall.log', 'a')
write_f.write(str("MakePSF: %s" % final_part))
write_f.write('\n')
write_f.close()

#print "makePB!"
#write_f=open('casa5_data_pysynthesisimager_clean_500_0-13_mosaic_psfonly_parall.log', 'a')
#write_f.write(str("MAKE PB" ))
#write_f.write('\n')
#write_f.close()

#imager.makePB()
#print "runMajorCycle!"
#start = time.time()
#imager.runMajorCycle() # Make initial dirty / residual image
#end = time.time()
#final_part = (end - start)
#print("runMajorCycle_inital:", final_part)
#write_f=open('casa5_data_pysynthesisimager_clean_500_0-13_mosaic_psfonly_parall.log', 'a')
#write_f.write(str("runMajorCycle_inital: %s" % final_part))
#write_f.write('\n')
#write_f.close()


## (6) Make the initial clean mask
#imager.hasConverged()
#imager.updateMask()

## (7) Run the iteration loops
#print "entry while loop"
#write_f=open('casa5_data_pysynthesisimager_clean_500_0-13_mosaic_psfonly_parall.log', 'a')
#write_f.write(str("ENTER WHILE LOOP" ))
#write_f.write('\n')
#write_f.close()
#while ( not imager.hasConverged() ):
#    start = time.time()
#    imager.runMinorCycle()
#    end = time.time()
#    final_part = (end - start)
#    print("runMinorCycle_inloop:", final_part)
#    write_f=open('casa5_data_pysynthesisimager_clean_500_0-13_mosaic_psfonly_parall.log', 'a')
#    write_f.write(str("runMinorCycle_inloop: %s" % final_part))
#    write_f.write('\n')
#    write_f.close()

#    start = time.time()
#    imager.runMajorCycle()
#    end = time.time()
#    final_part = (end - start)
#    print("runMajorCycle_inloop:", final_part)
#    write_f=open('casa5_data_pysynthesisimager_clean_500_0-13_mosaic_psfonly_parall.log', 'a')
#    write_f.write(str("runMajorCycle_inloop: %s" % final_part))
#    write_f.write('\n')
#    write_f.close()

#    imager.updateMask()

## (8) Finish up

#retrec=imager.getSummary(); #does not work due to tkinter
#print "restoreImages!"
#imager.restoreImages()
#print "pbcorImages!"
#imager.pbcorImages()

## (9) Close tools.
print "deleteTools!"
imager.deleteTools()

#----------------------
#For major cycle parallelization for continuum imaging (specmode='mfs'),
#replace steps (1) and (3) with the following
#from imagerhelpers.imager_parallel_continuum import PyParallelContSynthesisImager      # Step (1)
#imager = PyParallelContSynthesisImager(params=paramList)                                  # Step (3)
#--------------
#For parallelization of both the major and minor cycles for Cube imaging, replace steps (1) and (3) with the following,
#and include a virtual concanenation call at the end.
#from imagerhelpers.imager_parallel_cube import PyParallelCubeSynthesisImager   # Step (1)
#imager = PyParallelCubeSynthesisImager(params=paramList)                         # Step (3)
#imager.concatImages(type='virtualcopy')                                           # Step (8)
