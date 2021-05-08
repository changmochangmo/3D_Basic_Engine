xof 0303txt 0032
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

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}

template VertexDuplicationIndices {
 <b8d65549-d7c9-4995-89cf-53a9a8b031e3>
 DWORD nIndices;
 DWORD nOriginalVertices;
 array DWORD indices[nIndices];
}

template FVFData {
 <b6e70a0e-8ef9-4e83-94ad-ecc8b0c04897>
 DWORD dwFVF;
 DWORD nDWords;
 array DWORD data[nDWords];
}


Frame capsule_shadow {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh capsule_shadow {
  12;
  8.752962;0.000001;-15.160563;,
  0.000008;0.000000;-17.505915;,
  -8.752949;-0.000001;-15.160573;,
  15.160566;0.000002;8.752958;,
  17.505915;0.000003;0.000003;,
  15.160568;0.000002;-8.752954;,
  8.752958;0.000001;15.160566;,
  0.000001;0.000000;17.505915;,
  -15.160566;-0.000002;8.752958;,
  -17.505915;-0.000003;0.000000;,
  -15.160562;-0.000002;-8.752968;,
  -8.752956;-0.000001;15.160568;;
  10;
  3;0,1,2;,
  3;3,4,5;,
  3;6,3,5;,
  3;7,6,5;,
  3;5,8,7;,
  3;5,0,8;,
  3;9,8,0;,
  3;0,2,9;,
  3;2,10,9;,
  3;8,11,7;;

  MeshNormals {
   12;
   -0.000000;1.000000;-0.000000;,
   -0.000000;1.000000;-0.000000;,
   -0.000000;1.000000;-0.000000;,
   -0.000000;1.000000;0.000000;,
   -0.000000;1.000000;0.000000;,
   -0.000000;1.000000;-0.000000;,
   -0.000000;1.000000;0.000000;,
   -0.000000;1.000000;-0.000000;,
   -0.000000;1.000000;-0.000000;,
   -0.000000;1.000000;-0.000000;,
   -0.000000;1.000000;0.000000;,
   -0.000000;1.000000;-0.000000;;
   10;
   3;0,1,2;,
   3;3,4,5;,
   3;6,3,5;,
   3;7,6,5;,
   3;5,8,7;,
   3;5,0,8;,
   3;9,8,0;,
   3;0,2,9;,
   3;2,10,9;,
   3;8,11,7;;
  }

  MeshTextureCoords {
   12;
   0.250244;0.932129;,
   0.499756;0.999023;,
   0.749512;0.932129;,
   0.067383;0.250244;,
   0.000499;0.499756;,
   0.067383;0.749512;,
   0.250244;0.067383;,
   0.500000;0.000499;,
   0.932129;0.250244;,
   0.999023;0.500000;,
   0.932129;0.749512;,
   0.749512;0.067383;;
  }

  MeshMaterialList {
   1;
   10;
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0;

   Material {
    1.000000;1.000000;1.000000;1.000000;;
    10.000000;
    0.000000;0.000000;0.000000;;
    0.000000;0.000000;0.000000;;

    TextureFilename {
     "Capsule_Shadow_capsule_shadow";
    }
   }
  }

  VertexDuplicationIndices {
   12;
   12;
   0,
   1,
   2,
   3,
   4,
   5,
   6,
   7,
   8,
   9,
   10,
   11;
  }

  FVFData {
   258;
   24;
   960143360,
   1052467200,
   960126976,
   1059209216,
   1040793600,
   1063100416,
   1059209216,
   960135168,
   1052467200,
   960135168,
   1040793600,
   1040793600,
   1063100416,
   1040793600,
   1065345024,
   1052467200,
   1063100416,
   1063100416,
   1059209216,
   1065345024,
   1052467200,
   1065345024,
   1065345024,
   1059209216;
  }
 }
}
