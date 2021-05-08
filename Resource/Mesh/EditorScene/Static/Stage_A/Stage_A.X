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


Frame cardboard_Stage {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh cardboard_Stage {
  16;
  447.93763;89.220704;-185.752499;,
  -447.41597;-37.912192;-185.752422;,
  -447.41597;89.220704;-185.752422;,
  447.93763;-37.912192;-185.752499;,
  -447.41597;89.220704;-185.752422;,
  -447.41597;-37.912192;-185.752422;,
  -447.41597;89.220717;185.709901;,
  -447.41597;-37.912179;185.709901;,
  447.93763;-37.912192;-185.752499;,
  447.93763;89.220704;-185.752499;,
  447.93766;-37.912179;185.709901;,
  447.93766;89.220717;185.709901;,
  -447.41597;89.220717;185.709901;,
  447.93766;89.220717;185.709901;,
  447.93763;89.220704;-185.752499;,
  -447.41597;89.220704;-185.752422;;
  8;
  3;0,1,2;,
  3;0,3,1;,
  3;4,5,6;,
  3;5,7,6;,
  3;8,9,10;,
  3;9,11,10;,
  3;12,13,14;,
  3;14,15,12;;

  MeshNormals {
   16;
   -0.000000;0.000000;-1.000000;,
   -0.000000;0.000000;-1.000000;,
   -0.000000;0.000000;-1.000000;,
   -0.000000;0.000000;-1.000000;,
   -1.000000;0.000000;0.000000;,
   -1.000000;0.000000;0.000000;,
   -1.000000;0.000000;0.000000;,
   -1.000000;0.000000;0.000000;,
   1.000000;0.000000;-0.000000;,
   1.000000;0.000000;-0.000000;,
   1.000000;0.000000;-0.000000;,
   1.000000;0.000000;-0.000000;,
   -0.000000;1.000000;-0.000000;,
   0.000000;1.000000;-0.000000;,
   -0.000000;1.000000;-0.000000;,
   -0.000000;1.000000;-0.000000;;
   8;
   3;0,1,2;,
   3;0,3,1;,
   3;4,5,6;,
   3;5,7,6;,
   3;8,9,10;,
   3;9,11,10;,
   3;12,13,14;,
   3;14,15,12;;
  }

  MeshTextureCoords {
   16;
   0.895996;0.726074;,
   0.103455;0.994629;,
   0.103088;0.726074;,
   0.896484;0.994629;,
   0.103088;0.726074;,
   0.004345;0.725586;,
   0.102661;0.005795;,
   0.004345;0.005795;,
   0.994141;0.725586;,
   0.895996;0.726074;,
   0.994141;0.005795;,
   0.895508;0.005795;,
   0.102661;0.005795;,
   0.895508;0.005795;,
   0.895996;0.726074;,
   0.103088;0.726074;;
  }

  MeshMaterialList {
   1;
   8;
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
     "Stage_A_PropStage_2048px.tga";
    }
   }
  }

  VertexDuplicationIndices {
   16;
   8;
   0,
   1,
   2,
   3,
   2,
   1,
   6,
   7,
   3,
   0,
   10,
   11,
   6,
   11,
   0,
   2;
  }
 }
}
