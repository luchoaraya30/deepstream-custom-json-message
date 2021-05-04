#include <gst/gst.h>
#include <glib.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include "gstnvdsmeta.h"
#include "nvds_analytics_meta.h"
#include "custom_payload.h"


// This is just to remember the unique-id of SGIE's 
#define SGIE_CAR_COLOR_UNIQUE_ID  4
#define SGIE_CAR_TYPE_UNIQUE_ID 5
#define SGIE_PERSON_GENDER_UNIQUE_ID 6
#define SGIE_PERSON_AGE_UNIQUE_ID 7


// Update CustomPayloadMeta (user_data) with SGIE's meta
extern "C" void custom_parse_sgie_meta_data (NvDsMetaList *l_class, CustomPayloadMeta *user_data)
{
	// Get meta from classifier_meta_list
        NvDsClassifierMeta *classifier_meta = (NvDsClassifierMeta *) l_class->data;
	
	// Iterate label_info_list
        for (GList *l_info = classifier_meta->label_info_list; l_info != NULL; l_info = l_info->next) {
                // Get meta from one of the SGIE's
		NvDsLabelInfo *label_info = (NvDsLabelInfo *) l_info->data;
		
		// Save meta in CustomPayloadMeta structure
                switch (classifier_meta->unique_component_id) {
                        case 4:  user_data->car_color = label_info->result_label;
                                 break;
                        case 5:  user_data->car_type = label_info->result_label;
                                 break;
                        case 6:  user_data->person_gender = label_info->result_label;
                                 break;
                        case 7:  user_data->person_age = label_info->result_label;
                                 break;
                }
        }
}

