#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/Random.h"
#include "/home/codeleaded/System/Static/Library/Splines.h"
#include "/home/codeleaded/System/Static/Library/TransformedView.h"


TransformedView tv;
float freq = 0.1f;

float RGA_New_P_F(float p){
    return RGA_New_P(p);
}

void Setup(AlxWindow* w){
    tv = TransformedView_Make(
        (Vec2){ GetWidth(),GetHeight() },
        (Vec2){ 0.0f,0.0f },
        (Vec2){ 0.01f,0.01f },
        (float)GetWidth() / (float)GetHeight()
    );
    
}
void Update(AlxWindow* w){
    TransformedView_HandlePanZoom(&tv,w->Strokes,GetMouse());
    const Vec2 m = TransformedView_ScreenWorldPos(&tv,GetMouse());
    
    if(Stroke(ALX_KEY_UP).DOWN)     freq *= 1.01f;
    if(Stroke(ALX_KEY_DOWN).DOWN)   freq *= 0.99f;

    Clear(BLACK);

    //for(int x = 0;x<GetWidth();x++){
    //    const float wx = TransformedView_ScreenWorldX(&tv,x);
    //    const float px = (float)RGA_New_P(floor(wx));
    //    const float l = px;
    //    Rect_RenderXX(WINDOW_STD_ARGS,x,(1.0f - l) * GetHeight(),1,l * GetHeight(),WHITE);
    //}

    //for(int x = 0;x<GetWidth();x++){
    //    const float wx = TransformedView_ScreenWorldX(&tv,x);
    //    const float t = wx - floorf(wx);
    //    
    //    const float px0 = (float)floorf(wx) - 1.0f;
    //    const float px1 = (float)floorf(wx);
    //    const float px2 = (float)ceilf(wx);
    //    const float px3 = (float)ceilf(wx) + 1.0f;
    //
    //    const float py0 = (float)RGA_New_P(px0);
    //    const float py1 = (float)RGA_New_P(px1);
    //    const float py2 = (float)RGA_New_P(px2);
    //    const float py3 = (float)RGA_New_P(px3);
    //    
    //    const Vec2 out = CRSpline_Calc(
    //        (Vec2){ px0,py0 },
    //        (Vec2){ px1,py1 },
    //        (Vec2){ px2,py2 },
    //        (Vec2){ px3,py3 },
    //        t
    //    );
    //    const float l = out.y;
    //    Rect_RenderXX(WINDOW_STD_ARGS,x,(1.0f - l) * GetHeight(),1,l * GetHeight(),WHITE);
    //}

    //for(int y = 0;y<GetHeight();y++){
    //    const float wy = TransformedView_ScreenWorldY(&tv,y);
    //    const float ty = wy - floorf(wy);
    //    
    //    const float ypx0 = (float)floorf(wy) - 1.0f;
    //    const float ypx1 = (float)floorf(wy);
    //    const float ypx2 = (float)ceilf(wy);
    //    const float ypx3 = (float)ceilf(wy) + 1.0f;
    //    const float ypy0 = (float)RGA_New_P(ypx0);
    //    const float ypy1 = (float)RGA_New_P(ypx1);
    //    const float ypy2 = (float)RGA_New_P(ypx2);
    //    const float ypy3 = (float)RGA_New_P(ypx3);
    //    
    //    const Vec2 outy = CRSpline_Calc(
    //        (Vec2){ ypx0,ypy0 },
    //        (Vec2){ ypx1,ypy1 },
    //        (Vec2){ ypx2,ypy2 },
    //        (Vec2){ ypx3,ypy3 },
    //        ty
    //    );
    //
    //    for(int x = 0;x<GetWidth();x++){
    //        const float wx = TransformedView_ScreenWorldX(&tv,x);
    //        const float tx = wx - floorf(wx);
    //        
    //        const float xpx0 = (float)floorf(wx) - 1.0f;
    //        const float xpx1 = (float)floorf(wx);
    //        const float xpx2 = (float)ceilf(wx);
    //        const float xpx3 = (float)ceilf(wx) + 1.0f;
    //        const float xpy0 = (float)RGA_New_P(xpx0);
    //        const float xpy1 = (float)RGA_New_P(xpx1);
    //        const float xpy2 = (float)RGA_New_P(xpx2);
    //        const float xpy3 = (float)RGA_New_P(xpx3);
    //        
    //        const Vec2 outx = CRSpline_Calc(
    //            (Vec2){ xpx0,xpy0 },
    //            (Vec2){ xpx1,xpy1 },
    //            (Vec2){ xpx2,xpy2 },
    //            (Vec2){ xpx3,xpy3 },
    //            tx
    //        );
    //
    //        //const float t = (tx + ty) * 0.5f;
    //        //const float st = 3.0f * t * t - 2.0f * t * t * t;
    //        //const float l = ((1.0f - st) * outx.y + st * outy.y) * 0.5f;
    //
    //        //const float l = (outx.y + outy.y) * 0.5f;
    //        const Pixel c = Pixel_toRGBA(l,l,l,1.0f);
    //        w->Buffer[y * GetWidth() + x] = c;
    //    }
    //}

    const Vec2 tl = TransformedView_ScreenWorldPos(&tv,(Vec2){ 0.0f,0.0f });
    const Vec2 br = TransformedView_ScreenWorldPos(&tv,(Vec2){ GetWidth(),GetHeight() });
    const Vec2 sd = TransformedView_WorldScreenLength(&tv,(Vec2){ 1.0f,1.0f });

    for(float y = floorf(tl.y);y<br.y;y+=1.0f){
        for(float x = floorf(tl.x);x<br.x;x+=1.0f){
            const float t = freq * y;

            const Vec2 out0 = CRSpline_Calc_F(x,floorf(t) - 1.0f,   freq,RGA_New_P_F);
            const Vec2 out1 = CRSpline_Calc_F(x,floorf(t),          freq,RGA_New_P_F);
            const Vec2 out2 = CRSpline_Calc_F(x,ceilf(t),           freq,RGA_New_P_F);
            const Vec2 out3 = CRSpline_Calc_F(x,ceilf(t) + 1.0f,    freq,RGA_New_P_F);
    
            const Vec2 out = CRSpline_Calc(
                out0,
                out1,
                out2,
                out3,
                t - floor(t)
            );

            //const float l = F32_Sigmoid((out.x + out.y) * 0.5f);
            const float l = F32_Sigmoid(5.0f * (out.y - 0.5f));
            //const float l = F32_Clamp(out.y,0.0f,1.0f);
            const Pixel c = Pixel_toRGBA(l,l,l,1.0f);
            const Vec2 sp = TransformedView_WorldScreenPos(&tv,(Vec2){ x,y });
            Rect_RenderXX(WINDOW_STD_ARGS,sp.x,sp.y,sd.x + 1.0f,sd.y + 1.0f,c);
        }
    }

    //for(int y = 0;y<GetHeight();y++){
    //    for(int x = 0;x<GetWidth();x++){
    //        const Vec2 p = TransformedView_ScreenWorldPos(&tv,(Vec2){ x,y });
    //        const float px = (float)((double)RGA_New_P(p.x) / (double)RANDOM_MAX);
    //        const float py = (float)((double)RGA_New_P(p.y) / (double)RANDOM_MAX);
    //
    //        const float l = px;
    //        const Pixel c = Pixel_toRGBA(l,l,l,1.0f);
    //        w->Buffer[y * GetWidth() + x] = c;
    //    }
    //}

    CStr_RenderAlxFontf(WINDOW_STD_ARGS,GetAlxFont(),0.0f,0.0f,RED,"F: %f",freq);
}
void Delete(AlxWindow* w){
    
}

int main(){
    if(Create("Hill Noise",900,500,2,2,Setup,Update,Delete))
        Start();
    return 0;
}