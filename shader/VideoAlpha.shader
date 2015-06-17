Shader "Custom/HorizontalGrayscaleAlphaMask" {
 
    Properties
    {
        _MainTex("Main Texture",2D) = "white"{}
		_AlphaOffset ("Alpha offset", float) = 0.5
    }
   
    SubShader
    {
       Tags {"Queue"="Transparent" "IgnoreProjector"="True" "RenderType"="Transparent"}
       
        CGPROGRAM
        #pragma surface surf Lambert alpha
        
            struct Input
            {
                float4 color : COLOR;
                float2 uv_MainTex;
            };
           
            sampler2D _MainTex;
			float _AlphaOffset;
   
            void surf (Input IN, inout SurfaceOutput o)
            {
				half4 c = tex2D(_MainTex, IN.uv_MainTex);			
                half4 a = tex2D (_MainTex, IN.uv_MainTex + float2(_AlphaOffset, 0) );	
                if(IN.uv_MainTex.x < _AlphaOffset)
                {            
					o.Albedo = c.rgb;
					o.Alpha  = Luminance(a.rgb);
				}
            }
        ENDCG
    }
   
    Fallback "Diffuse"
 
}
