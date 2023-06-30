#ifndef OBJECTVISITOR_H
#define OBJECTVISITOR_H

#include <memory>

#include "camera.h"
#include "carcassmodel.h"
#include "modelstructure.h"
#include "basedrawer.h"

using namespace std;

class ObjectVisitor
{
public:
    virtual ~ObjectVisitor() = default;

    virtual void visit(const std::shared_ptr<Object> &object) = 0;
    virtual void visit(Camera& camera) = 0;
    virtual void visit(CarcassModel& model) = 0;

    void set_ptr(weak_ptr<ObjectVisitor> ptr) { _self_ptr = ptr; }

protected:
    weak_ptr<ObjectVisitor> _self_ptr;
};

#endif // OBJECTVISITOR_H
