# How to use:

 * create a shader with the script written by LouLou from the french forum http://www.unity3d-france.com 
http://www.unity3d-france.com/unity/phpBB3/viewtopic.php?f=8&t=901
 * Apply this shader to a material, and adjust the Tile and offset of the texture of this material to hide the white alpha image.
 
```csharp
Shader "Custom/VideoAlpha" {
   Properties {
      _MainTex ("Base (RGB)", 2D) = "white" {}
      _AlphaOffsetX ("alpha offset x", float) = 0.5
      _AlphaOffsetY ("alpha offset y", float) = 0
      _Cutoff ("Cutoff", Range (0,1)) = .5
   }
   SubShader {
   AlphaTest Less [_Cutoff]
         CGPROGRAM
         #pragma surface surf Lambert
   
         sampler2D _MainTex;
         float _AlphaOffsetX;
         float _AlphaOffsetY;
   
         struct Input {
            float2 uv_MainTex;
         };
   
         void surf (Input IN, inout SurfaceOutput o) {
            half4 c = tex2D (_MainTex, IN.uv_MainTex);
            IN.uv_MainTex.x += _AlphaOffsetX;
            IN.uv_MainTex.y += _AlphaOffsetY;
            half4 d = tex2D (_MainTex, IN.uv_MainTex);
            o.Albedo = c.rgb;
            o.Alpha = (d.r*-1)+1;
         }
         ENDCG
     
   }
   FallBack "Diffuse"
}
```

source: http://forum.unity3d.com/threads/chroma-key-shader.48938/
