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


Frame sign_jazzclub {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh sign_jazzclub {
  18;
  0.000000;0.000000;-0.000656;,
  63.490195;126.980390;-0.000626;,
  63.490195;0.000000;-0.000656;,
  0.000000;126.980390;-0.000626;,
  0.000002;110.594854;0.000643;,
  3.395878;110.594854;0.000643;,
  0.000002;126.980390;0.000645;,
  21.719154;110.594854;0.000643;,
  63.490195;126.980390;0.000645;,
  63.490195;110.594854;0.000643;,
  63.490195;0.000004;0.000633;,
  21.719150;23.472835;0.000635;,
  0.000002;0.000004;0.000633;,
  3.395880;23.455554;0.000635;,
  3.395878;110.594854;0.000643;,
  21.719150;23.472835;0.000635;,
  21.719154;110.594854;0.000643;,
  3.395880;23.455554;0.000635;;
  14;
  3;0,1,2;,
  3;3,1,0;,
  3;4,5,6;,
  3;6,5,7;,
  3;6,7,8;,
  3;8,7,9;,
  3;9,7,10;,
  3;10,7,11;,
  3;12,10,11;,
  3;12,11,13;,
  3;12,13,4;,
  3;4,13,5;,
  3;14,15,16;,
  3;17,15,14;;

  MeshNormals {
   18;
   0.000000;0.000000;-1.000000;,
   0.000000;0.000000;-1.000000;,
   0.000000;0.000000;-1.000000;,
   0.000000;0.000000;-1.000000;,
   0.000000;-0.000000;1.000000;,
   -0.000000;-0.000000;1.000000;,
   0.000000;-0.000000;1.000000;,
   -0.000000;-0.000000;1.000000;,
   0.000000;-0.000000;1.000000;,
   0.000000;-0.000000;1.000000;,
   -0.000000;-0.000000;1.000000;,
   -0.000000;-0.000000;1.000000;,
   0.000000;-0.000000;1.000000;,
   0.000000;-0.000000;1.000000;,
   -0.000000;-0.000000;1.000000;,
   -0.000000;-0.000000;1.000000;,
   -0.000000;-0.000000;1.000000;,
   0.000000;-0.000000;1.000000;;
   14;
   3;0,1,2;,
   3;3,1,0;,
   3;4,5,6;,
   3;6,5,7;,
   3;6,7,8;,
   3;8,7,9;,
   3;9,7,10;,
   3;10,7,11;,
   3;12,10,11;,
   3;12,11,13;,
   3;12,13,4;,
   3;4,13,5;,
   3;14,15,16;,
   3;17,15,14;;
  }

  MeshTextureCoords {
   18;
   0.000031;1.000000;,
   1.000000;0.000031;,
   1.000000;1.000000;,
   0.000031;0.000031;,
   0.000031;0.129028;,
   0.053467;0.129028;,
   0.000031;0.000031;,
   0.342041;0.129028;,
   1.000000;0.000031;,
   1.000000;0.129028;,
   1.000000;1.000000;,
   0.342041;0.814941;,
   0.000031;1.000000;,
   0.053467;0.814941;,
   0.342041;0.129028;,
   0.053467;0.814941;,
   0.053467;0.129028;,
   0.342041;0.814941;;
  }

  MeshMaterialList {
   1;
   14;
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
     "Sign_Jazzculb_sign_jazzclubneon.tga";
    }
   }
  }

  VertexDuplicationIndices {
   18;
   14;
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
   5,
   11,
   7,
   13;
  }
 }
}
