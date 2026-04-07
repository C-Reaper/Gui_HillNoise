#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/Random.h"
#include "/home/codeleaded/System/Static/Library/Splines.h"
#include "/home/codeleaded/System/Static/Library/TransformedView.h"


TransformedView tv;

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
    

    Clear(BLACK);

    //for(int x = 0;x<GetWidth();x++){
    //    const float wx = TransformedView_ScreenWorldX(&tv,x);
    //    const float px = (float)RGA_New_P(floor(wx));
    //    const float l = px;
    //    Rect_RenderXX(WINDOW_STD_ARGS,x,(1.0f - l) * GetHeight(),1,l * GetHeight(),WHITE);
    //}


    const Vec2 tl = TransformedView_ScreenWorldPos(&tv,(Vec2){ 0.0f,0.0f });
    const Vec2 br = TransformedView_ScreenWorldPos(&tv,(Vec2){ GetWidth(),GetHeight() });
    const Vec2 sd = TransformedView_WorldScreenLength(&tv,(Vec2){ 1.0f,1.0f });

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

    for(int y = 0;y<GetHeight();y++){
        const float wy = TransformedView_ScreenWorldY(&tv,y);
        const float ty = wy - floorf(wy);
        
        const float ypx0 = (float)floorf(wy) - 1.0f;
        const float ypx1 = (float)floorf(wy);
        const float ypx2 = (float)ceilf(wy);
        const float ypx3 = (float)ceilf(wy) + 1.0f;
        const float ypy0 = (float)RGA_New_P(ypx0);
        const float ypy1 = (float)RGA_New_P(ypx1);
        const float ypy2 = (float)RGA_New_P(ypx2);
        const float ypy3 = (float)RGA_New_P(ypx3);
        
        const Vec2 outy = CRSpline_Calc(
            (Vec2){ ypx0,ypy0 },
            (Vec2){ ypx1,ypy1 },
            (Vec2){ ypx2,ypy2 },
            (Vec2){ ypx3,ypy3 },
            ty
        );

        for(int x = 0;x<GetWidth();x++){
            const float wx = TransformedView_ScreenWorldX(&tv,x);
            const float tx = wx - floorf(wx);
            
            const float xpx0 = (float)floorf(wx) - 1.0f;
            const float xpx1 = (float)floorf(wx);
            const float xpx2 = (float)ceilf(wx);
            const float xpx3 = (float)ceilf(wx) + 1.0f;
            const float xpy0 = (float)RGA_New_P(xpx0);
            const float xpy1 = (float)RGA_New_P(xpx1);
            const float xpy2 = (float)RGA_New_P(xpx2);
            const float xpy3 = (float)RGA_New_P(xpx3);
            
            const Vec2 outx = CRSpline_Calc(
                (Vec2){ xpx0,xpy0 },
                (Vec2){ xpx1,xpy1 },
                (Vec2){ xpx2,xpy2 },
                (Vec2){ xpx3,xpy3 },
                tx
            );

            //const float t = (tx + ty) * 0.5f;
            //const float st = 3.0f * t * t - 2.0f * t * t * t;
            //const float l = ((1.0f - st) * outx.y + st * outy.y) * 0.5f;

            //const float l = (outx.y + outy.y) * 0.5f;
            const Pixel c = Pixel_toRGBA(l,l,l,1.0f);
            w->Buffer[y * GetWidth() + x] = c;
        }
    }

    //for(float y = tl.y;y<br.y;y+=1.0f){
    //    for(float x = tl.x;x<br.x;x+=1.0f){
    //        const float px = (float)RGA_New_P(x);
    //        const float py = (float)RGA_New_P(y);
    //
    //        const float l = (px + py) * 0.5f;
    //        const Pixel c = Pixel_toRGBA(l,l,l,1.0f);
    //        
    //        const Vec2 sp = TransformedView_WorldScreenPos(&tv,(Vec2){ x,y });
    //        Rect_RenderXX(WINDOW_STD_ARGS,sp.x,sp.y,sd.x,sd.y,c);
    //    }
    //}

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
}
void Delete(AlxWindow* w){
    
}

int main(){
    if(Create("Hill Noise",900,500,2,2,Setup,Update,Delete))
        Start();
    return 0;
}