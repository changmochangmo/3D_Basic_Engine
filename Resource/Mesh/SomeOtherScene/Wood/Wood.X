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


Frame Plane_ {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh Plane_ {
  16;
  -0.000010;160.000000;-159.999987;,
  -0.000003;160.000000;-53.333325;,
  -0.000010;53.333331;-160.000000;,
  0.000010;53.333325;160.000000;,
  0.000003;53.333328;53.333331;,
  0.000010;160.000000;160.000013;,
  0.000003;160.000000;53.333341;,
  -0.000003;53.333328;-53.333331;,
  -0.000010;-53.333331;-160.000000;,
  -0.000003;-53.333334;-53.333341;,
  -0.000010;-160.000000;-160.000013;,
  -0.000003;-160.000000;-53.333347;,
  0.000003;-53.333334;53.333325;,
  0.000003;-160.000000;53.333318;,
  0.000010;-53.333341;160.000000;,
  0.000010;-160.000000;159.999987;;
  18;
  3;0,1,2;,
  3;3,4,5;,
  3;6,5,4;,
  3;4,7,6;,
  3;1,6,7;,
  3;7,2,1;,
  3;2,7,8;,
  3;9,8,7;,
  3;8,9,10;,
  3;11,10,9;,
  3;9,12,11;,
  3;13,11,12;,
  3;12,14,13;,
  3;15,13,14;,
  3;7,4,9;,
  3;12,9,4;,
  3;4,3,12;,
  3;14,12,3;;

  MeshNormals {
   16;
   1.000000;0.000000;-0.000000;,
   1.000000;0.000000;-0.000000;,
   1.000000;0.000000;-0.000000;,
   1.000000;0.000000;-0.000000;,
   1.000000;0.000000;-0.000000;,
   1.000000;0.000000;-0.000000;,
   1.000000;0.000000;-0.000000;,
   1.000000;0.000000;-0.000000;,
   1.000000;0.000000;-0.000000;,
   1.000000;0.000000;-0.000000;,
   1.000000;0.000000;-0.000000;,
   1.000000;0.000000;-0.000000;,
   1.000000;0.000000;-0.000000;,
   1.000000;0.000000;-0.000000;,
   1.000000;0.000000;-0.000000;,
   1.000000;0.000000;-0.000000;;
   18;
   3;0,1,2;,
   3;3,4,5;,
   3;6,5,4;,
   3;4,7,6;,
   3;1,6,7;,
   3;7,2,1;,
   3;2,7,8;,
   3;9,8,7;,
   3;8,9,10;,
   3;11,10,9;,
   3;9,12,11;,
   3;13,11,12;,
   3;12,14,13;,
   3;15,13,14;,
   3;7,4,9;,
   3;12,9,4;,
   3;4,3,12;,
   3;14,12,3;;
  }

  MeshTextureCoords {
   16;
   0.000031;0.000031;,
   0.333252;0.000031;,
   0.000031;0.333252;,
   1.000000;0.333252;,
   0.666504;0.333252;,
   1.000000;0.000031;,
   0.666504;0.000031;,
   0.333252;0.333252;,
   0.000031;0.666504;,
   0.333252;0.666504;,
   0.000031;1.000000;,
   0.333252;1.000000;,
   0.666504;0.666504;,
   0.666504;1.000000;,
   1.000000;0.666504;,
   1.000000;1.000000;;
  }

  MeshMaterialList {
   1;
   18;
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
     "Wood_walkway_wood.tga";
    }
   }
  }

  VertexDuplicationIndices {
   16;
   16;
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
   11,
   12,
   13,
   14,
   15;
  }
 }
}
