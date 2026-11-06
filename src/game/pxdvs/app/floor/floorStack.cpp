#include <dolphin/types.h>

#pragma peephole off

struct GSthread;
struct FloorData;
struct GSfloor_dd_;
struct AppScript;

enum FloorState {
    FLOOR_STATE_0
};

class GSresID {
public:
    void set(u32 group, u32 id);
    void clear();

    u32 m_group;
    u32 m_id;
};

class FloorStack {
public:
    FloorStack();
    void addResource(u32 group, u32 id);
    void freeAllResource();
    void freeResource(u32 group, u32 id);
    void unblock();
    void block();
    void reallocPushData();
    void setPushState(void* data, u32 size);
    void setGroupID(u32 groupID);
    void setFloorID(u32 floorID);
    u32 getFloorID() const;
    int getObjective();
    void clearFlag();
    void setPopFlag();
    void setPushFlag();
    void clear();
    AppScript* getScriptModule();
    void makeScriptModule();
    void setUpdateState(FloorState state);

    u32 m_groupID;
    u32 m_floorID;
    void* m_pushData;
    u32 m_pushSize;
    u8 m_pushFlag;
    u8 m_popFlag;
    AppScript* m_script;
    u32 m_unk18;
    GSthread* m_thread;
    GSresID m_resources[64];
    u32 m_unk220;
};

class FloorStackList {
public:
    FloorStackList(u32 num);
    ~FloorStackList();
    void unblock();
    void block();
    void setGroupID(u32 groupID);
    void setPushState(void* data, u32 size);
    void setUpdateState(FloorState state);
    int getObjective();
    GSfloor_dd_* getGSfloor();
    int getStateMode();
    FloorStack* pop();
    FloorStack* push(unsigned int floorID);
    u32 getGroupID();
    FloorStack* getCurrentStack();

    FloorStack* m_stacks;
    s32 m_depth;
    u32 m_num;
};

AppScript* scriptCreateAppScript();

extern "C" {
void GSthreadUnblockGroup(u32 group);
void GSthreadBlockGroup(u32 group);
void GSthreadUnblock(GSthread* thread);
void GSthreadBlock(GSthread* thread);
void GSthreadSetGroupID(GSthread* thread, u32 group);
FloorData* floorDataBiosGetPtr(u32 id);
u8 floorDataBiosGetFloorKind(FloorData* data);
void GSresFreeResource(u32 group, u32 id);
void* GSmemAlloc(u32 size);
void GSmemFree(void* ptr);
void* memcpy(void* dst, const void* src, unsigned long n);
void* memset(void* dst, int c, unsigned long n);
}

void FloorStackList::unblock() {
    GSthreadUnblockGroup(getGroupID());
    getCurrentStack()->unblock();
}

void FloorStackList::block() {
    GSthreadBlockGroup(getGroupID());
    getCurrentStack()->block();
}

void FloorStackList::setGroupID(u32 groupID) {
    FloorStack* stack = getCurrentStack();
    stack->setGroupID(groupID);
    stack->unblock();
}

void FloorStackList::setPushState(void* data, u32 size) {
    getCurrentStack()->setPushState(data, size);
}

void FloorStackList::setUpdateState(FloorState state) {
    getCurrentStack()->setUpdateState(state);
}

int FloorStackList::getObjective() {
    return getCurrentStack()->getObjective();
}

GSfloor_dd_* FloorStackList::getGSfloor() {
    return (GSfloor_dd_*)floorDataBiosGetPtr(getCurrentStack()->getFloorID());
}

int FloorStackList::getStateMode() {
    u8 kind = floorDataBiosGetFloorKind(floorDataBiosGetPtr(getCurrentStack()->getFloorID()));
    if (kind == 1) {
        return 1;
    }
    if (kind == 2) {
        return 2;
    }
    return 0;
}

FloorStack* FloorStackList::pop() {
    FloorStack* stack;
    m_depth--;
    stack = getCurrentStack();
    stack->setPopFlag();
    return stack;
}

FloorStack* FloorStackList::push(unsigned int floorID) {
    FloorStack* stack;
    m_depth++;
    stack = getCurrentStack();
    stack->clear();
    stack->setPushFlag();
    stack->setFloorID(floorID);
    return stack;
}

FloorStackList::~FloorStackList() {
    if (m_stacks != NULL) {
        delete m_stacks;
        m_stacks = NULL;
    }
}

FloorStackList::FloorStackList(u32 num) {
    u32 i;
    m_stacks = new FloorStack[num];
    m_depth = 0;
    m_num = num;
    for (i = 0; i < num; i++) {
        m_stacks[i].makeScriptModule();
    }
}

void FloorStack::addResource(u32 group, u32 id) {
    GSresID* res;
    for (res = m_resources; res != &m_resources[64]; res++) {
        if (res->m_group == group && res->m_id == id) {
            GSresFreeResource(res->m_group, res->m_id);
            return;
        }
    }
    for (res = m_resources; res != &m_resources[64]; res++) {
        if (res->m_group == 0) {
            res->set(group, id);
            return;
        }
    }
}

void FloorStack::freeAllResource() {
    GSresID* res;
    for (res = m_resources; res != &m_resources[64]; res++) {
        if (res->m_group != 0) {
            GSresFreeResource(res->m_group, res->m_id);
        }
    }
    memset(m_resources, 0, sizeof(m_resources));
}

void FloorStack::freeResource(u32 group, u32 id) {
    GSresID* res;
    for (res = m_resources; res != &m_resources[64]; res++) {
        if (res->m_group == group && res->m_id == id) {
            GSresFreeResource(res->m_group, res->m_id);
            res->clear();
            return;
        }
    }
}

void FloorStack::unblock() {
    if (m_thread != NULL) {
        GSthreadUnblock(m_thread);
    }
}

void FloorStack::block() {
    if (m_thread != NULL) {
        GSthreadBlock(m_thread);
    }
}

void FloorStack::reallocPushData() {
    void* data = GSmemAlloc(m_pushSize);
    if (data != NULL) {
        memcpy(data, m_pushData, m_pushSize);
        GSmemFree(m_pushData);
        m_pushData = data;
    }
}

void FloorStack::setPushState(void* data, u32 size) {
    m_pushData = data;
    m_pushSize = size;
}

void FloorStack::setGroupID(u32 groupID) {
    m_groupID = groupID;
    if (m_thread != NULL) {
        GSthreadSetGroupID(m_thread, groupID + 0x2000);
    }
}

void FloorStack::setFloorID(u32 floorID) {
    m_floorID = floorID;
    m_groupID = floorID + 0x5001;
}

int FloorStack::getObjective() {
    if (m_pushFlag) {
        return 1;
    }
    if (m_popFlag) {
        return 2;
    }
    return 3;
}

void FloorStack::clearFlag() {
    m_pushFlag = 0;
    m_popFlag = 0;
}

void FloorStack::setPopFlag() {
    m_pushFlag = 0;
    m_popFlag = 1;
}

void FloorStack::setPushFlag() {
    m_pushFlag = 1;
    m_popFlag = 0;
}

void FloorStack::clear() {
    m_groupID = 0;
    m_pushData = NULL;
    m_pushFlag = 0;
    m_popFlag = 0;
    m_unk18 = 0;
    m_unk220 = 0;
    m_thread = NULL;
    memset(m_resources, 0, sizeof(m_resources));
}

AppScript* FloorStack::getScriptModule() {
    return m_script;
}

void FloorStack::makeScriptModule() {
    if (m_script == NULL) {
        m_script = scriptCreateAppScript();
    }
}

#pragma dont_inline on
FloorStack::FloorStack() {
    clear();
    m_script = NULL;
    m_thread = NULL;
}
#pragma dont_inline reset

inline void GSresID::set(u32 group, u32 id) {
    m_group = group;
    m_id = id;
}

inline void GSresID::clear() {
    m_group = 0;
    m_id = 0;
}
