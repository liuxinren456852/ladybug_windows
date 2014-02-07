#include "ladybug5_windows_client.h"

std::string indent(int level) {
  std::string s; 
  for (int i=0; i<level; i++) s += "  ";
  return s; 
} 

void printTree (boost::property_tree::ptree &pt, int level) {
  if (pt.empty()) {
    std::cout << "\""<< pt.data()<< "\"";
  } else {
    if (level) std::cout << std::endl; 
    std::cout << indent(level) << "{" << std::endl;     
    for (boost::property_tree::ptree::iterator pos = pt.begin(); pos != pt.end();) {
      std::cout << indent(level+1) << "\"" << pos->first << "\": "; 
      printTree(pos->second, level + 1); 
      ++pos; 
      if (pos != pt.end()) {
        std::cout << ","; 
      }
      std::cout << std::endl;
    } 
    std::cout << indent(level) << " }";     
  }
  return; 
}

void createDefaultIni(boost::property_tree::ptree *pt){
    pt->put("Network.ROS_MASTER", cfg_ros_master.c_str());  
    pt->put("Threading.Enabled", cfg_threading);
    pt->put("Threading.NumberCompressionThreads", cfg_compression_threads); 
    pt->put("Threading.OneThreadPerImageGrab", cfg_full_img_msg);
    pt->put("Settings.PostProcessing", cfg_postprocessing);      
    pt->put("Ladybug.Simulate", cfg_simulation);
    pt->put("Ladybug.Panoramic_Only", cfg_panoramic);  
    pt->put("Ladybug.PanoWidth", cfg_pano_width);
    pt->put("Ladybug.PanoHight", cfg_pano_hight);
    pt->put("Ladybug.ColorProcessing", ladybugColorProcessingMap.left.find(cfg_ladybug_colorProcessing)->second.c_str());
    pt->put("Ladybug.Dataformat", ladybugDataFormatMap.left.find(cfg_ladybug_dataformat)->second.c_str());
    boost::property_tree::ini_parser::write_ini(cfg_configFile.c_str(), *pt);
}

void loadConfigsFromPtree(boost::property_tree::ptree *pt){
    cfg_ros_master = pt->get<std::string>("Network.ROS_MASTER");
    cfg_threading = pt->get<bool>("Threading.Enabled");
    cfg_compression_threads = pt->get<unsigned int>("Threading.NumberCompressionThreads");
    cfg_full_img_msg = pt->get<bool>("Threading.OneThreadPerImageGrab");
    cfg_postprocessing = pt->get<bool>("Settings.PostProcessing");
    cfg_simulation = pt->get<bool>("Ladybug.Simulate");
    cfg_panoramic = pt->get<bool>("Ladybug.Panoramic_Only");
    cfg_pano_width = pt->get<int>("Ladybug.PanoWidth");
    cfg_pano_hight = pt->get<unsigned int>("Ladybug.PanoHight");
    cfg_ladybug_colorProcessing = ladybugColorProcessingMap.right.find( pt->get<std::string>("Ladybug.ColorProcessing"))->second;    
    cfg_ladybug_dataformat = ladybugDataFormatMap.right.find( pt->get<std::string>("Ladybug.Dataformat"))->second;
}

const ldf_type ladybugDataFormatMap =
  boost::assign::list_of< ldf_type::relation >
    ( LADYBUG_DATAFORMAT_RAW8, "RAW8" )
    ( LADYBUG_DATAFORMAT_JPEG8, "JPEG8" )
    ( LADYBUG_DATAFORMAT_COLOR_SEP_RAW8, "COLOR_SEP_RAW8" )
    ( LADYBUG_DATAFORMAT_COLOR_SEP_JPEG8, "COLOR_SEP_JPEG8" )
    ( LADYBUG_DATAFORMAT_HALF_HEIGHT_RAW8, "HALF_HEIGHT_RAW8" )
    ( LADYBUG_DATAFORMAT_COLOR_SEP_RAW8, "COLOR_SEP_RAW8" )
    ( LADYBUG_DATAFORMAT_COLOR_SEP_HALF_HEIGHT_JPEG8, "COLOR_SEP_HALF_HEIGHT_JPEG8" )
    ( LADYBUG_DATAFORMAT_COLOR_SEP_JPEG12, "COLOR_SEP_JPEG12" )
    ( LADYBUG_DATAFORMAT_HALF_HEIGHT_RAW16, "HALF_HEIGHT_RAW16" )
    ( LADYBUG_DATAFORMAT_COLOR_SEP_HALF_HEIGHT_JPEG12, "COLOR_SEP_HALF_HEIGHT_JPEG12" )
    ( LADYBUG_DATAFORMAT_RAW12, "RAW12" )
    ( LADYBUG_DATAFORMAT_HALF_HEIGHT_RAW12, "HALF_HEIGHT_RAW12" );

const lcpm_type ladybugColorProcessingMap =
    boost::assign::list_of< lcpm_type::relation >
    ( LADYBUG_DISABLE, "DISABLE" )
    ( LADYBUG_EDGE_SENSING, "EDGE_SENSING" )
    ( LADYBUG_NEAREST_NEIGHBOR_FAST, "NEAREST_NEIGHBOR_FAST" )
    ( LADYBUG_RIGOROUS, "RIGOROUS" )
    ( LADYBUG_DOWNSAMPLE4, "DOWNSAMPLE4" )
    ( LADYBUG_DOWNSAMPLE16, "DOWNSAMPLE16" )
    ( LADYBUG_MONO, "MONO" )
    ( LADYBUG_HQLINEAR, "HQLINEAR" )
    ( LADYBUG_HQLINEAR_GPU, "HQLINEAR_GPU" )
    ( LADYBUG_DIRECTIONAL_FILTER, "DIRECTIONAL_FILTER" )
    ( LADYBUG_COLOR_FORCE_QUADLET, "COLOR_FORCE_QUADLET" );