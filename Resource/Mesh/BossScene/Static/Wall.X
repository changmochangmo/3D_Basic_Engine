xof 0303txt 0032
template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}

template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshNormals {
 <f6f23f43-7686-11cf-8f52-0040333594a3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template Coords2d {
 <f6f23f44-7686-11cf-8f52-0040333594a3>
 FLOAT u;
 FLOAT v;
}

template MeshTextureCoords {
 <f6f23f40-7686-11cf-8f52-0040333594a3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}


Material Material__158 {
 1.000000;1.000000;1.000000;1.000000;;
 10.000000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "Castle_wall.tga";
 }
}

Frame castle_wall_01 {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh castle_wall_01 {
  8;
  2181.87162;1877.41504;-0.000061;,
  2181.87162;0.000061;0.000000;,
  0.000000;1877.41504;-0.000061;,
  0.000000;0.000000;0.000000;,
  2181.87162;-874.47162;0.000000;,
  0.000000;-874.47162;0.000000;,
  0.000000;0.000000;0.000000;,
  2181.87162;0.000061;0.000000;;
  4;
  3;0,1,2;,
  3;2,1,3;,
  3;4,5,6;,
  3;6,7,4;;

  MeshNormals {
   8;
   0.000000;-0.000000;-1.000000;,
   0.000000;-0.000000;-1.000000;,
   0.000000;-0.000000;-1.000000;,
   0.000000;-0.000000;-1.000000;,
   0.000000;0.000000;-1.000000;,
   0.000000;0.000000;-1.000000;,
   0.000000;-0.000000;-1.000000;,
   0.000000;-0.000000;-1.000000;;
   4;
   3;0,1,2;,
   3;2,1,3;,
   3;4,5,6;,
   3;6,7,4;;
  }

  MeshMaterialList {
   1;
   4;
   0,
   0,
   0,
   0;
   { Material__158 }
  }

  MeshTextureCoords c1 {
   8;
   1.000000;0.000031;,
   1.000000;1.000000;,
   0.000031;0.000031;,
   0.000031;1.000000;,
   1.996094;1.000977;,
   -0.499268;1.000977;,
   -0.499268;0.000688;,
   1.996094;0.000688;;
  }

  MeshTextureCoords c2 {
   8;
   0.994629;0.005550;,
   0.994629;0.680664;,
   0.004948;0.005550;,
   0.004948;0.680664;,
   0.994629;0.995606;,
   0.004948;0.995606;,
   0.004948;0.680664;,
   0.994629;0.680664;;
  }
 }
}