#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/TransformedView.h"
#include "/home/codeleaded/System/Static/Library/HillNoise.h"


TransformedView tv;
char mode = 0;
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
    
    if(Stroke(ALX_KEY_UP).DOWN)         freq *= 1.01f;
    if(Stroke(ALX_KEY_DOWN).DOWN)       freq *= 0.99f;
    if(Stroke(ALX_KEY_SPACE).PRESSED)   mode = !mode;

    Clear(BLACK);

    if(mode == 0){
        const Vec2 tl = TransformedView_ScreenWorldPos(&tv,(Vec2){ 0.0f,0.0f });
        const Vec2 br = TransformedView_ScreenWorldPos(&tv,(Vec2){ GetWidth(),GetHeight() });
        const Vec2 sd = TransformedView_WorldScreenLength(&tv,(Vec2){ 1.0f,1.0f });

        for(float x = floorf(tl.x);x<br.x;x+=1.0f){
            const float l = HillNoise_1D(x,freq);
            const float sx = TransformedView_WorldScreenX(&tv,x);
            Rect_RenderXX(WINDOW_STD_ARGS,sx,(1.0f - l) * GetHeight(),sd.x + 1.0f,l * GetHeight(),WHITE);
        }
    }else{
        const Vec2 tl = TransformedView_ScreenWorldPos(&tv,(Vec2){ 0.0f,0.0f });
        const Vec2 br = TransformedView_ScreenWorldPos(&tv,(Vec2){ GetWidth(),GetHeight() });
        const Vec2 sd = TransformedView_WorldScreenLength(&tv,(Vec2){ 1.0f,1.0f });

        for(float y = floorf(tl.y);y<br.y;y+=1.0f){
            for(float x = floorf(tl.x);x<br.x;x+=1.0f){
                const float l = HillNoise_2D(x,y,freq);
                const Pixel c = Pixel_toRGBA(l,l,l,1.0f);
                const Vec2 sp = TransformedView_WorldScreenPos(&tv,(Vec2){ x,y });
                Rect_RenderXX(WINDOW_STD_ARGS,sp.x,sp.y,sd.x + 1.0f,sd.y + 1.0f,c);
            }
        }
    }

    CStr_RenderAlxFontf(WINDOW_STD_ARGS,GetAlxFont(),0.0f,0.0f,RED,"F: %f",freq);
}
void Delete(AlxWindow* w){
    
}

int main(){
    if(Create("Hill Noise",900,500,2,2,Setup,Update,Delete))
        Start();
    return 0;
}