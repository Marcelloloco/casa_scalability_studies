# 1535.36494 GB
from cngi.direct import InitializeFramework
from cngi.conversion import convert_ms
client = InitializeFramework(workers=32, memory='20GB')
print(client)
chunks=(800, 3200, 160, 8)
mxds = convert_ms('/lfs/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/', outfile='Antennae_North.vis.zarr', chunks=chunks)