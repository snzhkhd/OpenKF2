#include "recomp.h"
#include "disable_warnings.h"
#include "PsyX/PsyX_public.h"
#include "PsyX/PsyX_render.h"
#include "gpu/PsyX_GPU.h"
#include "psx/libetc.h"
#include <string>

static int SaveCount = 0;
static int SaveTimer = 0;

void TriggerGpuDma(uint8_t* rdram, recomp_context* ctx) 
{
    uint32_t madr = ctx->r4;
    if (madr < 0x80000000 || madr >= 0x80200000) {
        ctx->r2 = 0;
        return;
    }

    // Передаём напрямую в PsyX - он сам умеет ходить по PS1 OTag!
    uint32_t phys = madr & 0x1FFFFF;
    u_long* ot_ptr = (u_long*)&rdram[phys];

    DrawOTag(ot_ptr); // ← PsyX сам вызовет ParsePrimitivesLinkedList + DrawAllSplits

    PsyX_EndScene();

    if (g_vsync_pending) {
        VSync(0);
        g_vsync_pending = false;
    }

    ctx->r2 = 0;
    //uint32_t madr = ctx->r4;
    //if (madr < 0x80000000 || madr >= 0x80200000) return;

    //uint32_t* p_data = (uint32_t*)GET_PTR(madr);
    //uint32_t first_word = p_data[0];
    //uint32_t next_ptr = first_word & 0x00FFFFFF;
    //uint8_t  top_byte = (first_word >> 24) & 0xFF;

    //if (next_ptr >= 0x00010000 && next_ptr < 0x001FFFFF && top_byte < 0x20)
    //{
    //    uint32_t cur_addr = madr;
    //    while (true) {
    //        uint32_t* cur = (uint32_t*)GET_PTR(cur_addr);
    //        uint32_t tag = cur[0];
    //        uint8_t  len = (tag >> 24) & 0xFF;
    //        uint32_t next = tag & 0x00FFFFFF;

    //     //   printf("[Walk] addr=0x%08X tag=0x%08X len=%d next=0x%06X\n",
    //     //       cur_addr, tag, len, next);

    //        if (len > 0) 
    //        {
    //            static uint8_t psyx_prim[128];
    //            memset(psyx_prim, 0, 128);

    //            // addr = NULL (bytes 0-7)
    //            // len/pgxp = 0 (bytes 8-11)
    //            *(uint32_t*)(psyx_prim + 8) = (uint32_t)len;

    //            psyx_prim[12] = (cur[1] >> 0) & 0xFF;  // pad0 (r0)
    //            psyx_prim[13] = (cur[1] >> 8) & 0xFF;  // pad1 (g0)
    //            psyx_prim[14] = (cur[1] >> 16) & 0xFF;  // pad2 (b0)
    //            psyx_prim[15] = (cur[1] >> 24) & 0xFF;  // code = 0x2E ← здесь!

    //            // данные примитива начиная с byte 16
    //            memcpy(&psyx_prim[16], &cur[2], (len - 1) * 4);

    //            if (psyx_prim[15] == 0x2E || psyx_prim[15] == 0x3E ||   
    //                psyx_prim[15] == 0x26 || psyx_prim[15] == 0x36) {
    //                // Semi-transparent textured poly — убираем semi-transparency флаг
    //                // Правильное решение: настроить GR_SetBlendMode перед рендером
    //                // Временный фикс:
    //                psyx_prim[15] &= ~0x02; // убираем бит semi-transparency
    //            }
    //            printf("[Before ParsePrim] g_splitIndex=%d\n", g_splitIndex);
    //            ParsePrimitivesLinkedList((u_long*)psyx_prim, 0);
    //            printf("[After ParsePrim] g_splitIndex=%d\n", g_splitIndex);

    //        }

    //        if (next == 0x00FFFFFF || next < 0x00010000) break;
    //        cur_addr = next | 0x80000000;
    //    }
    //   

    //    
    //    DrawAllSplits();
    //    printf("[DispEnv] disp x=%d y=%d w=%d h=%d\n",
    //        activeDispEnv.disp.x, activeDispEnv.disp.y,
    //        activeDispEnv.disp.w, activeDispEnv.disp.h);

    //   
    //    PsyX_EndScene();
    //    if (g_vsync_pending) 
    //    {
    //        VSync(0);
    //        g_vsync_pending = false;

    //        SaveTimer++;
    //        if (SaveTimer > 20 && SaveCount < 5)
    //        {
    //            SaveTimer = 0;
    //            std::string str = "vram_debug_" + std::to_string(SaveCount) + ".png";
    //            GR_SaveVRAM(str.c_str(), 0, 0, 1024, 512, 0);
    //            SaveCount++;
    //            printf("[DEBUG] VRAM saved to %s\n", str.c_str());
    //        }
    //    }
    //    
    //}
    //else if (top_byte == 0x00 && (first_word & 0xFF) <= 0x20)
    //{
    //    uint32_t* packet_start = p_data + 1;
    //    
    //    ParsePrimitivesLinkedList((unsigned long*)packet_start, 1);
    //}
    //else
    //{
    //   
    //    ParsePrimitivesLinkedList((unsigned long*)p_data, 1);
    //}

    WRITE_W(0x1F8010A8, MEM_W(0, 0x1F8010A8) & ~0x01000000);
    WRITE_W(0x1F801814, 0x1C000000);
    ctx->r2 = 0;
}
    //uint64_t hi = 0, lo = 0, result = 0;
    //unsigned int rounding_mode = DEFAULT_ROUNDING_MODE;
    //int c1cs = 0; 
    //// lui         $v1, 0x400
    //ctx->r3 = S32(0X400 << 16);
    //// lui         $v0, 0x8007
    //ctx->r2 = S32(0X8007 << 16);
    //// lw          $v0, 0x6274($v0)
    //ctx->r2 = MEM_W(0X6274, ctx->r2);
    //// ori         $v1, $v1, 0x2
    //ctx->r3 = ctx->r3 | 0X2;
    //// sw          $v1, 0x0($v0)
    //MEM_W(0X0, ctx->r2) = ctx->r3;
    //// lui         $v0, 0x8007
    //ctx->r2 = S32(0X8007 << 16);
    //// lw          $v0, 0x6278($v0)
    //ctx->r2 = MEM_W(0X6278, ctx->r2);
    //// nop

    //// sw          $a0, 0x0($v0)
    //MEM_W(0X0, ctx->r2) = ctx->r4;
    //// lui         $v0, 0x8007
    //ctx->r2 = S32(0X8007 << 16);
    //// lw          $v0, 0x627C($v0)
    //ctx->r2 = MEM_W(0X627C, ctx->r2);
    //// lui         $v1, 0x100
    //ctx->r3 = S32(0X100 << 16);
    //// sw          $zero, 0x0($v0)
    //MEM_W(0X0, ctx->r2) = 0;
    //// lui         $v0, 0x8007
    //ctx->r2 = S32(0X8007 << 16);
    //// lw          $v0, 0x6280($v0)
    //ctx->r2 = MEM_W(0X6280, ctx->r2);
    //// ori         $v1, $v1, 0x401
    //ctx->r3 = ctx->r3 | 0X401;
    //// sw          $v1, 0x0($v0)
    //MEM_W(0X0, ctx->r2) = ctx->r3;
    //// jr          $ra
    //// nop

    //return;
    //// nop

