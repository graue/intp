void regstk(void);
void regstr(void);
void regctl(void);
void regnum(void);
#define VERIFY(vj, typ)							\
if (vj->vtyp != typ) error("wanted vtyp " #typ " got %d", vj->vtyp)
#define BLTN(nam) addbltn(#nam, nam);
