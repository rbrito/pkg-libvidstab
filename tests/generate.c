#define NUM_RECTANGLES 100
void generateFrames(TestData* testdata, int num){
  int i;
  for(i=0; i<num; i++){
		allocateFrame(&testdata->frames[i],&testdata->fi);
  }
  // first frame noise
  fillArrayWithNoise(testdata->frames[0].data[0],
										 testdata->fi.width*testdata->fi.height, 10);
  fillArrayWithNoise(testdata->frames[0].data[1],
										 testdata->fi.width/2*testdata->fi.height/2, 5);
	fillArrayWithNoise(testdata->frames[0].data[2],
										 testdata->fi.width/2*testdata->fi.height/2, 5);

  // add rectangles
  int k;
  for(k=0; k<NUM_RECTANGLES; k++){
    paintRectangle(testdata->frames[0].data[0],&testdata->fi,
									 randUpTo(testdata->fi.width), randUpTo(testdata->fi.height),
									 randUpTo((testdata->fi.width>>4)+4),
									 randUpTo((testdata->fi.height>>4)+4),randPixel());

  }

  TransformData td;
  test_bool(initTransformData(&td, &testdata->fi, &testdata->fi, "generate") == VS_OK);
  td.interpolType=Zero;
  test_bool(configureTransformData(&td)== VS_OK);


  fprintf(stderr, "testframe transforms\n");

  for(i=1; i<num; i++){
    Transform t = getTestFrameTransform(i);
    fprintf(stderr, "%i, %6.4lf %6.4lf %8.5lf %6.4lf %i\n",
						i, t.x, t.y, t.alpha, t.zoom, t.extra);

    test_bool(transformPrepare(&td,&testdata->frames[i-1],&testdata->frames[i])== VS_OK);
    test_bool(transformYUV_float(&td, t)== VS_OK);
    test_bool(transformFinish(&td)== VS_OK);
  }
  cleanupTransformData(&td);
}

/*
 * Local variables:
 *   c-file-style: "stroustrup"
 *   c-file-offsets: ((case-label . *) (statement-case-intro . *))
 *   indent-tabs-mode: nil
 *   c-basic-offset: 2 t
 * End:
 *
 * vim: expandtab shiftwidth=2:
 */
