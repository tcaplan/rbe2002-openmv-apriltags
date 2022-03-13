Edited version of the example python scripts from OpenMV.

Both uart and i2c versions have been tested with their uC counterparts (`examples/apriltag_finder_x`) for a single tag. Untested for multiple tags.

The high resolution (`hires`) versions are experimental. They first find blobs of interest and then 'zoom in' on those areas, which saves memory and processing power (it's easier to find a blob than an apriltag). They have not been updated for the newest AprilTagDatum structure, though.
