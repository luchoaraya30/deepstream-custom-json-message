# Deepstream Custom test 5
Custom application based on deepstream-test5 to generate a custom JSON message, plugin nvmsgconv is also modified to generate the custom schema. All work was done with docker image *nvcr.io/nvidia/deepstream:5.1-21.02-triton* and tested with kafka broker.

## Define JSON message
Files  [custom_payload.h](includes/custom_payload.h) and [nvdsmeta_schema.h](includes/nvdsmeta_schema.h)

We will send the next message with PGIE and SGIE metadata:

![Alt text](../images/custom_json_msg.png?raw=true "Title")

- Define **CustomPayloadMeta** structure where the information to generate the payment will be stored.
- Add the same parameters of the newly defined structure to the **NvDsEventMsgMeta** structure.

## nvmsgconv
File [nvmsgconv.cpp](libs/nvmsgconv/nvmsgconv.cpp)

By default msgconv generates a static payload that contains a lot of junk information. The original definition contemplates 5 schemas; place, sensor, analytics, event and object. To generate our message only one schema is needed, so we will take the analytics schema as a base and modify it to our convenience.

- Modify function **generate_analytics_module_object** to generate message according to our structure.
- Modify function **generate_schema_message** to avoid generating unwanted information.

## deepstream-test5

Files [deepstream_test5_app_main.c](deepstream-custom-test5/deepstream_test5_app_main.c) and [deepstream_sgie_meta.cpp](deepstream-custom-test5/deepstream_sgie_meta.cpp)

- Include custom_payload.h
- Change **generate_event_event_msg_meta** input parameter (CustomPayloadMeta instead of NvDsObjectMeta ) and update **EventMsgMeta** structure with information from **CustomPayloadMeta**.
- Modify **bbox_generated_probe_after_analytics** function to update **CustomPayloadMeta** structure with frame and object information.

By default test5 does not use the classification information (sgie's) therefore a function is created to store information in **CustomPayloadMeta** (see [deepstream_sgie_meta.cpp](deepstream-custom-test5/deepstream_sgie_meta.cpp)) this function receives as input the classifier list of an object (classifier_meta_list) and an instance of **CustomPayloadMeta**.

- Before **bbox_generated_probe_after_analytics** declare newly created function and after getting object information call **custom_parse_sgie_meta_data**.
- Modify input parameter when calling **generate_event_msg_meta**.
- At the end of **bbox_generated_probe_after_analytics** free memory allocated to user_data (instance of **CustomPayloadMeta**).

PS: All modified code is delimited by the line **//----- CUSTOM CODE ------//**.

## Execution
- Copy the contents of *includes/* and *libs/* folders into *sources/includes/* and *sources/libs/* folders inside the deepstream docker.
- Compile and install **nvmsgconv** (export cuda and run make install)
- Copy folder *deepstream-custom-test5* to folder *sources/apps/sample_apps/*
- Compile application (export cuda and run make)
- Modify kafka server IP and topic to subscribe to in configuration file [test5_config_file_src_infer.txt](deepstream-custom-test5/configs/test5_config_file_src_infer.txt)
