/* Private experiment only. MPL-2.0. Included in riscv_cpu.c after the private state. */
#if defined(FLOE_PRIVATE_ACCEL) && MAX_XLEN == 64
enum {
    P_ADDI=1, P_XORI, P_ORI, P_ANDI, P_SLLI, P_SRLI, P_SRAI,
    P_ADD, P_SUB, P_XOR, P_OR, P_AND, P_SLL, P_SRL, P_SRA
};

static inline void floe_private_decode(uint32_t word, FloePrivateDecoded *d)
{
    uint32_t op=word&127, f3=(word>>12)&7, f7=word>>25;
    d->valid=1; d->instruction=word; d->kind=0;
    d->rd=(word>>7)&31; d->rs1=(word>>15)&31; d->rs2=(word>>20)&31;
    d->immediate=(int32_t)word>>20;
    if (op==0x13) {
        if (f3==0) d->kind=P_ADDI;
        else if (f3==4) d->kind=P_XORI;
        else if (f3==6) d->kind=P_ORI;
        else if (f3==7) d->kind=P_ANDI;
        else if (f3==1 && (word>>26)==0) d->kind=P_SLLI;
        else if (f3==5 && (word>>26)==0) d->kind=P_SRLI;
        else if (f3==5 && (word>>26)==0x10) d->kind=P_SRAI;
    } else if (op==0x33) {
        if (f7==0) {
            switch(f3) {
            case 0:d->kind=P_ADD;break; case 1:d->kind=P_SLL;break;
            case 4:d->kind=P_XOR;break; case 5:d->kind=P_SRL;break;
            case 6:d->kind=P_OR;break; case 7:d->kind=P_AND;break;
            }
        } else if (f7==0x20) {
            if (f3==0) d->kind=P_SUB;
            else if (f3==5) d->kind=P_SRA;
        }
    }
}

static inline int floe_private_predecoded(RISCVCPUState *s, uint32_t word)
{
    FloePrivateAccel *a=&s->private_accel;
    FloePrivateDecoded *d=&a->cache[((word>>2)^(word>>19))&127];
    uint64_t x,y,result;
    if (d->valid && d->instruction==word) a->cache_hits++;
    else { a->cache_misses++; floe_private_decode(word,d); }
    if (!d->kind) { a->fallbacks++; return 0; }
    x=s->reg[d->rs1]; y=s->reg[d->rs2];
    switch(d->kind) {
    case P_ADDI: result=x+(uint64_t)(int64_t)d->immediate;break;
    case P_XORI: result=x^(uint64_t)(int64_t)d->immediate;break;
    case P_ORI: result=x|(uint64_t)(int64_t)d->immediate;break;
    case P_ANDI: result=x&(uint64_t)(int64_t)d->immediate;break;
    case P_SLLI: result=x<<((uint32_t)d->immediate&63);break;
    case P_SRLI: result=x>>((uint32_t)d->immediate&63);break;
    case P_SRAI: result=(uint64_t)((int64_t)x>>((uint32_t)d->immediate&63));break;
    case P_ADD: result=x+y;break; case P_SUB: result=x-y;break;
    case P_XOR: result=x^y;break; case P_OR: result=x|y;break; case P_AND:result=x&y;break;
    case P_SLL: result=x<<(y&63);break; case P_SRL:result=x>>(y&63);break;
    case P_SRA:result=(uint64_t)((int64_t)x>>(y&63));break;
    default: return 0;
    }
    if (d->rd) s->reg[d->rd]=result;
    a->fast_instructions++;
    return 1;
}
#endif
