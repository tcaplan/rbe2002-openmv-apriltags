#include "apriltag_finder.h"

  void MyCamera::setup()
  {
    Serial.begin(115200);
    delay(1000);

    Wire.begin();
    Wire.setClock(100000ul);

    Serial.println(F("Welcome."));
  }

  uint8_t MyCamera::FindAprilTags()
  {
      uint8_t tagCount = camera2.getTagCount();
      if(tagCount) 
      {
        Serial.println(tagCount);
        AprilTagDatum tag;
        if(camera2.readTag(tag))
        {
          // Serial.print(F("Tag [cx="));
          // Serial.print(tag.cx);
          // Serial.print(F(", cy="));
          // Serial.print(tag.cy);
          // Serial.print(F(", w="));
          // Serial.print(tag.w);
          // Serial.print(F(", h="));
          // Serial.print(tag.h);
          // Serial.print(F(", id="));
          // Serial.print(tag.id);
          // Serial.print(F(", rot="));
          // Serial.print(tag.rot);
          // Serial.println(F("]"));
        }
      }

      return tagCount;
  }

  // DONT CALL THESE IF NOT SURE THERE IS AN APRIL TAG THERE
  uint16_t MyCamera::getCenterX() {
    if(FindAprilTags()) {
      AprilTagDatum tag;
      if(camera2.readTag(tag)) {
        return tag.cx;
      }
    }
    return 10000;
  }

  uint16_t MyCamera::getCenterY(void) {
    if(FindAprilTags()) {
      AprilTagDatum tag;
      if(camera2.readTag(tag)) {
        return tag.cy;
      }
    }
    return 10000;
  }

  uint16_t MyCamera::getWidth(void) {
    if(FindAprilTags()) {
      AprilTagDatum tag;
      if(camera2.readTag(tag)) {
        return tag.w;
      }
    }
    return 10000;
  }

  uint16_t MyCamera::getHeight(void) {
    if(FindAprilTags()) {
      AprilTagDatum tag;
      if(camera2.readTag(tag)) {
        return tag.h;
      }
    }
    return 10000;
  }

  uint16_t MyCamera::getID(void) {
    if(FindAprilTags()) {
      AprilTagDatum tag;
      if(camera2.readTag(tag)) {
        return tag.id;
      }
    }
    return 10000;
  }

  float MyCamera::getDistance(float tagSize) {

    if(FindAprilTags()) {
          float x_scale = 0.11 * 4.5 - 0.3;
      float y_scale = 0.017 * 4.5 + 0.8;
      float exponent = -0.207 * getHeight() - (122.406 * y_scale);
      float distance = pow(1.23, exponent) + (21.25 * x_scale);

      return distance;

    }
    return -1;
  }



  // void loop() 
  // { 
  //   delay(1); //calm things down for a sec...
  //   FindAprilTags();
  // }
