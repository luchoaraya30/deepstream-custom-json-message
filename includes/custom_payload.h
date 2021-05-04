#ifndef _CUSTOM_PAYLOAD_H_
#define _CUSTOM_PAYLOAD_H_

#include <gst/gst.h>

/* User defined */
typedef struct 
{
    // Object meta
    gint source_id;
    gint frame_id;
    gint object_id;
    gchar *object_class;
    // Bbox params
    float left;
    float top;
    float width;
    float height;
    // Classifier meta
    gchar *person_gender;
    gchar *person_age;
    gchar *car_color;
    gchar *car_type;

} CustomPayloadMeta;
#endif
