// This file is generated by Ember Desktop.  Please do not edit manually.
//
//

// This file contains the tokens for attributes stored in flash


// Identifier tags for tokens
// Creator for attribute: zone state, endpoint: 1
#define CREATOR_ZONE_STATE_1 0xB000
// Creator for attribute: zone type, endpoint: 1
#define CREATOR_ZONE_TYPE_1 0xB001
// Creator for attribute: IAS CIE address, endpoint: 1
#define CREATOR_IAS_CIE_ADDRESS_1 0xB002
// Creator for attribute: Zone ID, endpoint: 1
#define CREATOR_ZONE_ID_1 0xB003


// Types for the tokens
#ifdef DEFINETYPES
typedef uint8_t  tokType_ias_cie_address[8];
typedef uint8_t  tokType_zone_state;
typedef uint16_t  tokType_zone_type;
typedef uint8_t  tokType_zone_id;
#endif // DEFINETYPES


// Actual token definitions
#ifdef DEFINETOKENS
DEFINE_BASIC_TOKEN(ZONE_STATE_1, tokType_zone_state, 0x00)
DEFINE_BASIC_TOKEN(ZONE_TYPE_1, tokType_zone_type, 0x002a)
DEFINE_BASIC_TOKEN(IAS_CIE_ADDRESS_1, tokType_ias_cie_address, {0,0,0,0,0,0,0,0})
DEFINE_BASIC_TOKEN(ZONE_ID_1, tokType_zone_id, 0xff)
#endif // DEFINETOKENS


// Macro snippet that loads all the attributes from tokens
#define GENERATED_TOKEN_LOADER(endpoint) do {\
  uint8_t ptr[8]; \
  uint8_t curNetwork = emberGetCurrentNetwork(); \
  uint8_t epNetwork; \
  epNetwork = emberAfNetworkIndexFromEndpoint(1); \
  if((endpoint) == 1 || ((endpoint) == EMBER_BROADCAST_ENDPOINT && epNetwork == curNetwork)) { \
    halCommonGetToken((tokType_zone_state *)ptr, TOKEN_ZONE_STATE_1); \
    emberAfWriteServerAttribute(1, ZCL_IAS_ZONE_CLUSTER_ID, ZCL_ZONE_STATE_ATTRIBUTE_ID, (uint8_t*)ptr, ZCL_ENUM8_ATTRIBUTE_TYPE); \
    halCommonGetToken((tokType_zone_type *)ptr, TOKEN_ZONE_TYPE_1); \
    emberAfWriteServerAttribute(1, ZCL_IAS_ZONE_CLUSTER_ID, ZCL_ZONE_TYPE_ATTRIBUTE_ID, (uint8_t*)ptr, ZCL_ENUM16_ATTRIBUTE_TYPE); \
    halCommonGetToken((tokType_ias_cie_address *)ptr, TOKEN_IAS_CIE_ADDRESS_1); \
    emberAfWriteServerAttribute(1, ZCL_IAS_ZONE_CLUSTER_ID, ZCL_IAS_CIE_ADDRESS_ATTRIBUTE_ID, (uint8_t*)ptr, ZCL_IEEE_ADDRESS_ATTRIBUTE_TYPE); \
    halCommonGetToken((tokType_zone_id *)ptr, TOKEN_ZONE_ID_1); \
    emberAfWriteServerAttribute(1, ZCL_IAS_ZONE_CLUSTER_ID, ZCL_ZONE_ID_ATTRIBUTE_ID, (uint8_t*)ptr, ZCL_INT8U_ATTRIBUTE_TYPE); \
  } \
} while(false)


// Macro snippet that saves the attribute to token
#define GENERATED_TOKEN_SAVER do {\
  uint8_t allZeroData[8]; \
  MEMSET(allZeroData, 0, 8); \
  if ( data == NULL ) data = allZeroData; \
  if ( endpoint == 1 ) { \
    if ( clusterId == 0x0500 ) { \
      if ( metadata->attributeId == 0x0000 && !emberAfAttributeIsClient(metadata) ) \
        halCommonSetToken(TOKEN_ZONE_STATE_1, data); \
      if ( metadata->attributeId == 0x0001 && !emberAfAttributeIsClient(metadata) ) \
        halCommonSetToken(TOKEN_ZONE_TYPE_1, data); \
      if ( metadata->attributeId == 0x0010 && !emberAfAttributeIsClient(metadata) ) \
        halCommonSetToken(TOKEN_IAS_CIE_ADDRESS_1, data); \
      if ( metadata->attributeId == 0x0011 && !emberAfAttributeIsClient(metadata) ) \
        halCommonSetToken(TOKEN_ZONE_ID_1, data); \
    } \
  } \
} while(false)


