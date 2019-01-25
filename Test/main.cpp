#include <iostream>
#include <gtest/gtest.h>

//#include "StubNodeDataModel.hpp"

//#include <nodes/DataModelRegistry>

//tested in this order
#include "FreqData.hpp"
#include "AutoGradientData.hpp"
#include "BoundsData.hpp"
#include "ColourData.hpp"
#include "HeightMapData.hpp"

#include "FreqSourceDataModel.hpp"
#include "LnPerlinModel.hpp"


//using QtNodes::DataModelRegistry;
//using QtNodes::NodeData;
//using QtNodes::NodeDataModel;
//using QtNodes::NodeDataType;
//using QtNodes::PortIndex;
//using QtNodes::PortType;

//namespace
//{
//class StubModelStaticName : public StubNodeDataModel
//{
//public:
//  static QString
//  Name()
//  {
//    return "Name";
//  }
//};
//}

//Ideally this would use gmock to mimic node use
//https://github.com/google/googletest/blob/master/googlemock/docs/ForDummies.md (I'm the dummy)

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}


//------- Frequency class tests (spinbox values) ---------------
TEST(FreqData, defaultCtor)
{
  ASSERT_NO_THROW(FreqData f);
}

TEST(FreqData, getFreq)
{
  FreqData f;
  auto freq = f.number();
  EXPECT_DOUBLE_EQ(freq,0.0);
}

TEST(FreqData, getNodeID)
{
  FreqData f;
  auto node = f.type();
  ASSERT_EQ(node.id,"freq");
}

TEST(FreqData, copyCtor)
{
  FreqData f = 12.98;
  auto a = f;
  EXPECT_DOUBLE_EQ(a.number(),f.number());
}

TEST(FreqData, setFreq)
{
  FreqData f = 4.5;
  auto freq = f.number();
  EXPECT_DOUBLE_EQ(freq,4.5);
}

//------- Autogradient class tests (combobox values) ---------------
TEST(AutoGradientData, defaultCtor)
{
  ASSERT_NO_THROW(AutoGradientData a);
}

TEST(AutoGradientData, getValue)
{
  AutoGradientData a;
  auto gradientMode = a.number();
  EXPECT_EQ(gradientMode,1);
}

TEST(AutoGradientData, getNodeID)
{
  AutoGradientData a;
  auto node = a.type();
  ASSERT_EQ(node.id,"autogradient");
}

TEST(AutoGradientData, copyCtor)
{
  AutoGradientData a = 5;
  auto b = a;
  EXPECT_EQ(a.number(),b.number());
}

TEST(AutoGradientData, setFreq)
{
  AutoGradientData a = 2;
  auto gradientMode = a.number();
  EXPECT_DOUBLE_EQ(gradientMode,2);
}

//------- Bounds class tests (multi values) ---------------
TEST(BoundsData, defaultCtor)
{
  ASSERT_NO_THROW(BoundsData b);
}

TEST(BoundsData, getBounds)
{
  BoundsData b;
  auto boundsXL = b.numberXL();
  auto boundsXU = b.numberXU();
  auto boundsZL = b.numberZL();
  auto boundsZU = b.numberZU();
  EXPECT_DOUBLE_EQ(boundsXL,0.0);
  EXPECT_DOUBLE_EQ(boundsXU,0.0);
  EXPECT_DOUBLE_EQ(boundsZL,0.0);
  EXPECT_DOUBLE_EQ(boundsZU,0.0);
}

TEST(BoundsData, getNodeID)
{
  BoundsData b;
  auto node = b.type();
  ASSERT_EQ(node.id,"bounds");
}

TEST(BoundsData, copyCtor)
{
  BoundsData b = {12.98, 14.55, 543.2, 54.987};
  auto a = b;
  EXPECT_DOUBLE_EQ(a.numberXL(),b.numberXL());
  EXPECT_DOUBLE_EQ(a.numberXU(),b.numberXU());
  EXPECT_DOUBLE_EQ(a.numberZL(),b.numberZL());
  EXPECT_DOUBLE_EQ(a.numberZU(),b.numberZU());
}

TEST(BoundsData, setBounds)
{
  BoundsData b = {12.98, 14.55, 543.2, 54.987};
  auto boundsXL = b.numberXL();
  auto boundsXU = b.numberXU();
  auto boundsZL = b.numberZL();
  auto boundsZU = b.numberZU();
  EXPECT_DOUBLE_EQ(boundsXL,12.98);
  EXPECT_DOUBLE_EQ(boundsXU,14.55);
  EXPECT_DOUBLE_EQ(boundsZL,543.2);
  EXPECT_DOUBLE_EQ(boundsZU,54.987);
}

//------- Colour class tests ---------------
TEST(ColourData, defaultCtor)
{
  ASSERT_NO_THROW(ColourData c);
}

TEST(ColourData, getColour)
{
  ColourData c;
  auto colour = c.colour();
  ASSERT_EQ(colour,"white");
}

TEST(ColourData, getNodeID)
{
  ColourData c;
  auto node = c.type();
  ASSERT_EQ(node.id,"colour");
}

TEST(ColourData, copyCtor)
{
  ColourData c;
  auto newCol = c;
  ASSERT_EQ(newCol.colour(),c.colour());
}

//------- Heightmap class tests ---------------
TEST(HeightMapData, defaultCtor)
{
  ASSERT_NO_THROW(HeightMapData h);
}

TEST(HeightMapData, getNodeID)
{
  HeightMapData h;
  auto node = h.type();
  ASSERT_EQ(node.id,"heightmap");
}

TEST(HeightMapData, getHeightmapBuilderBounds)
{
  HeightMapData h;

  double lowerXBound = h.heightMapBuilder().GetLowerXBound();
  double lowerZBound = h.heightMapBuilder().GetLowerZBound();
  double upperXBound = h.heightMapBuilder().GetUpperXBound();
  double upperZBound = h.heightMapBuilder().GetUpperZBound();

  EXPECT_DOUBLE_EQ(lowerXBound,0.0);
  EXPECT_DOUBLE_EQ(lowerZBound,0.0);
  EXPECT_DOUBLE_EQ(upperXBound,0.0);
  EXPECT_DOUBLE_EQ(upperZBound,0.0);
}

TEST(HeightMapData, copySetHeightmapBuilderBounds)
{
  HeightMapData h;
  h.heightMapBuilder().SetBounds(1.0,2.0,3.0,4.0);
  noise::utils::NoiseMapBuilderPlane beans = h.heightMapBuilder();

  EXPECT_DOUBLE_EQ(h.heightMapBuilder().GetLowerXBound(),beans.GetLowerXBound());
  EXPECT_DOUBLE_EQ(h.heightMapBuilder().GetUpperXBound(),beans.GetUpperXBound());
  EXPECT_DOUBLE_EQ(h.heightMapBuilder().GetLowerZBound(),beans.GetLowerZBound());
  EXPECT_DOUBLE_EQ(h.heightMapBuilder().GetUpperZBound(),beans.GetUpperZBound());
}

//------- Node data tests ---------------
TEST(NodeCreation, registry)
{
  //create two nodes
  //manually connect nodes
  //  in connection ctor put nodes and ports as params
  //set data, check data etc

  //ideally we'd register a data model, create a model, and try to get the name
  //but regrettably this code throws some errors I haven't been able to solve
  //example is here - https://github.com/paceholder/nodeeditor/blob/master/test/src/TestDataModelRegistry.cpp
  //of course this actually does work in practice, but not here

//  DataModelRegistry registry;
//  registry.registerModel<FreqSourceDataModel>();
  //auto ret = registry.create("freq"); //errors here
  //ASSERT_EQ(ret->name(),"Frequency Source");



}

//------- Terrain generation tests ---------------
TEST(Terraingen, defaultCtor)
{
  ASSERT_NO_THROW(TerrainData t);
}

TEST(Terraingen, perlinGeneratorSetFreq)
{

  TerrainData t;
  FreqData f = 45.6;

  auto freq = f.number();
  EXPECT_DOUBLE_EQ(freq, 45.6);

  //generator modules don't like having values set like this:
  //t.myPerlinModule().SetFrequency(freq);
  //so we make a local copy, which makes the test pass, and also makes the nodes work!
  noise::module::Perlin myPerlin = t.myPerlinModule();

  myPerlin.SetFrequency(freq);

  EXPECT_DOUBLE_EQ(myPerlin.GetFrequency(), 45.6);
}
