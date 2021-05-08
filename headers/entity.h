#ifndef __ENTITY_H__
#define __ENTITY_H__

#ifdef __cplusplus
extern "C" {
#endif

    class Entity {
        public:
            virtual ~Entity ();
            virtual void draw();
        protected:
            Entity ();
        private:
            int x, y;
    };


#ifdef __cplusplus
}
#endif

#endif // __ENTITY_H__
