
#include "transform.h"
// #if defined(_DEBUG)
// 	#include "Logging.h"
// #endif

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

namespace ddd {

Transform Transform::Identity{};

Transform::Transform() noexcept
	: position{}
	, localPosition{}
	, scale{ 1.0f, 1.0f, 1.0f } 
	, localScale{ 1.0f, 1.0f, 1.0f }
	, rotation{}
	, localRotation{}
	, flags(0)
	, facing{ 0.0f, 0.0f, 1.0f }
	, parent{ nullptr }
	, worldMatrix{}
{
	worldMatrix.SetIdentity();
}
Transform::Transform(const ddd::Vector3& position_, const ddd::Quaternion& quaternion_, const ddd::Vector3& scale_) noexcept
	: position{ position_ }
	, localPosition{}
	, scale{ scale_ }
	, localScale{ 1.0f, 1.0f, 1.0f }
	, rotation{ quaternion_ }
	, localRotation{}
	, flags(0)
	, facing{ 0.0f, 0.0f, 1.0f }
	, parent{ nullptr }
	, worldMatrix{}
{}

//____________________________________________________________ setters
void Transform::SetFacingVector(const ddd::Vector3& zfacing) 
{
	facing = zfacing;
}
void Transform::SetAsBoneObject(bool isBoneObject_) 
{
	flags = isBoneObject_ ? (flags | T_ISBONE) : (flags & ~T_ISBONE);
}
void Transform::SetStatic(bool static_)
{
	flags = static_ ? (flags | T_STATIC) : (flags & ~T_STATIC);
	worldMatrix = BuildTRS4x4(position, rotation, scale);
}
void Transform::SetWorldFromMatrix(const ddd::Matrix44& matrix_)
{
	worldMatrix = matrix_;
	position	= ddd::GetPosition(matrix_);
	rotation	= ddd::GetRotation(matrix_);
	scale		= ddd::GetScale(matrix_);
}
void Transform::SetLocalFromMatrix(const ddd::Matrix44& matrix_)
{
	localPosition	= ddd::GetPosition(matrix_);
	localRotation	= ddd::GetRotation(matrix_);
	localScale		= ddd::GetScale(matrix_);
	flags |= T_DIRTY;
}

//____________________________________________________________ World
void Transform::SetPosition(float x_) {
	position.x = x_;
	flags |= T_DIRTY;
}
void Transform::SetPosition(float x_, float y_) {
	position.x = x_;
	position.y = y_;
	flags |= T_DIRTY;
}
void Transform::SetPosition(float x_, float y_, float z_) {
	position.x = x_;
	position.y = y_;
	position.z = z_;
	flags |= T_DIRTY;
}
void Transform::SetPosition(const ddd::Vector3& position_) {
	position.x = position_.x;
	position.y = position_.y;
	position.z = position_.z;
	flags |= T_DIRTY;
}
void Transform::SetRotation(float x_) {
	ddd::Vector3 eular{ ddd::ToEularDegree(rotation) };
	rotation.SetFromEulerAngles(ddd::Vector3{ x_, eular.y, eular.z });
	flags |= T_DIRTY;
}
void Transform::SetRotation(float x_, float y_) {
	rotation.SetFromEulerAngles(ddd::Vector3{ x_, y_, ddd::ToEularDegree(rotation).z });
	flags |= T_DIRTY;
}
void Transform::SetRotation(float x_, float y_, float z_) {
	rotation.SetFromEulerAngles(ddd::Vector3{ x_, y_, z_ });
	flags |= T_DIRTY;
}
void Transform::SetRotation(const ddd::Vector3& eular_) {
	rotation.SetFromEulerAngles(eular_);
	flags |= T_DIRTY;
}
void Transform::SetRotation(const ddd::Quaternion& rotation_) {
	rotation = rotation_;
	flags |= T_DIRTY;
}
void Transform::SetScale(float x_) {
	scale.x = x_;
	flags |= T_DIRTY;
}
void Transform::SetScale(float x_, float y_) {
	scale.x = x_;
	scale.y = y_;
	flags |= T_DIRTY;
}
void Transform::SetScale(float x_, float y_, float z_) {
	scale.x = x_;
	scale.y = y_;
	scale.z = z_;
	flags |= T_DIRTY;
}
void Transform::SetScale(const ddd::Vector3& scale_) {
	scale = scale_;
	flags |= T_DIRTY;
}
void Transform::SetUniformWorldScale2D(float xy_) {
	scale.y = scale.x = xy_;
	flags |= T_DIRTY;
}
void Transform::SetUniformWorldScale3D(float xyz_) {
	scale.z = scale.y = scale.x = xyz_;
	flags |= T_DIRTY;
}

//______________________________________________________________________ Local
void Transform::SetLocalPosition(float x_) {
	localPosition.x = x_;
	flags |= T_DIRTY | T_YET_TOUPDATE;
}
void Transform::SetLocalPosition(float x_, float y_) {
	localPosition.x = x_;
	localPosition.y = y_;
	flags |= T_DIRTY | T_YET_TOUPDATE;
}
void Transform::SetLocalPosition(float x_, float y_, float z_) {
	localPosition.x = x_;
	localPosition.y = y_;
	localPosition.z = z_;
	flags |= T_DIRTY | T_YET_TOUPDATE;
}
void Transform::SetLocalPosition(const ddd::Vector3& position_) {
	localPosition.x = position_.x;
	localPosition.y = position_.y;
	localPosition.z = position_.z;
	flags |= T_DIRTY | T_YET_TOUPDATE;
}
void Transform::SetLocalRotation(float x_) {
	ddd::Vector3 eular{ ddd::ToEularDegree(localRotation) };
	localRotation.SetFromEulerAngles(ddd::Vector3{ x_, eular.y, eular.z });
	flags |= T_DIRTY | T_YET_TOUPDATE;
}
void Transform::SetLocalRotation(float x_, float y_) {
	localRotation.SetFromEulerAngles(ddd::Vector3{ x_, y_, ddd::ToEularDegree(localRotation).z });
	flags |= T_DIRTY | T_YET_TOUPDATE;
}
void Transform::SetLocalRotation(float x_, float y_, float z_) {
	localRotation.SetFromEulerAngles(ddd::Vector3{ x_, y_, z_ });
	flags |= T_DIRTY | T_YET_TOUPDATE;
}
void Transform::SetLocalRotation(const ddd::Vector3& eular_) {
	localRotation.SetFromEulerAngles(eular_);
	flags |= T_DIRTY | T_YET_TOUPDATE;
}
void Transform::SetLocalRotation(const ddd::Quaternion& rotation_) {
	localRotation = rotation_;
	flags |= T_DIRTY | T_YET_TOUPDATE;
}
void Transform::SetLocalScale(float x_) {
	localScale.x = x_;
	flags |= T_DIRTY | T_YET_TOUPDATE;
}
void Transform::SetLocalScale(float x_, float y_) {
	localScale.x = x_;
	localScale.y = y_;
	flags |= T_DIRTY | T_YET_TOUPDATE;
}
void Transform::SetLocalScale(float x_, float y_, float z_) {
	localScale.x = x_;
	localScale.y = y_;
	localScale.z = z_;
	flags |= T_DIRTY | T_YET_TOUPDATE;
}
void Transform::SetLocalScale(const ddd::Vector3& scale_) {
	localScale = scale_;
	flags |= T_DIRTY | T_YET_TOUPDATE;
}
void Transform::SetUniformLocalScale2D(float xy_) {
	localScale.y = localScale.x = xy_;
	flags |= T_DIRTY | T_YET_TOUPDATE;
}
void Transform::SetUniformLocalScale3D(float xyz_) {
	localScale.z = localScale.y = localScale.x = xyz_;
	flags |= T_DIRTY | T_YET_TOUPDATE;
}

//____________________________________________________________ World
void Transform::Translate(float x_, float y_, float z_) {
	position.x += x_;
	position.y += y_;
	position.z += z_;
	flags |= T_DIRTY;
}
void Transform::Translate(const ddd::Vector3& translate_) {
	position += translate_;
	flags |= T_DIRTY;
}
void Transform::Rotate(float x_, float y_, float z_) {
	rotation *= ddd::ToQuaternion(ddd::Vector3{ x_, y_, z_ });
	flags |= T_DIRTY;
}
void Transform::Rotate(const ddd::Vector3& eular_) {
	rotation *= ddd::ToQuaternion(eular_);
	flags |= T_DIRTY;
}
void Transform::Rotate(const ddd::Quaternion& rotation_) {
	rotation *= rotation_;
	flags |= T_DIRTY;
}
void Transform::Scale(float x_, float y_, float z_) {
	scale.x += x_;
	scale.y += y_;
	scale.z += z_;
	flags |= T_DIRTY;
}
void Transform::Scale(const ddd::Vector3& scaling_) {
	scale.x += scaling_.x;
	scale.y += scaling_.y;
	scale.z += scaling_.z;
	flags |= T_DIRTY;
}
void Transform::ScaleMultiply(float x_, float y_, float z_) {
	scale.x *= x_;
	scale.y *= y_;
	scale.z *= z_;
	flags |= T_DIRTY;
}
void Transform::ScaleMultiply(const ddd::Vector3& scaling_) {
	scale.x *= scaling_.x;
	scale.y *= scaling_.y;
	scale.z *= scaling_.z;
	flags |= T_DIRTY;
}

//______________________________________________________________________ Local
void Transform::LocalTranslate(float x_, float y_, float z_) {
	localPosition.x += x_;
	localPosition.y += y_;
	localPosition.z += z_;
	flags |= T_DIRTY | T_YET_TOUPDATE;
}
void Transform::LocalTranslate(const ddd::Vector3& translate_) {
	localPosition += translate_;
	flags |= T_DIRTY | T_YET_TOUPDATE;
}
void Transform::LocalRotate(float x_, float y_, float z_) {
	localRotation *= ddd::ToQuaternion(ddd::Vector3{ x_, y_, z_ });
	flags |= T_DIRTY | T_YET_TOUPDATE;
}
void Transform::LocalRotate(const ddd::Vector3& eular__) {
	localRotation *= ddd::ToQuaternion(eular__);
	flags |= T_DIRTY | T_YET_TOUPDATE;
}
void Transform::LocalRotate(const ddd::Quaternion& rotation_) {
	localRotation *= rotation_;
	flags |= T_DIRTY | T_YET_TOUPDATE;
}
void Transform::LocalScale(float x_, float y_, float z_) {
	localScale.x += x_;
	localScale.y += y_;
	localScale.z += z_;
	flags |= T_DIRTY | T_YET_TOUPDATE;
}
void Transform::LocalScale(const ddd::Vector3& scaling_) {
	localScale.x += scaling_.x;
	localScale.y += scaling_.y;
	localScale.z += scaling_.z;
	flags |= T_DIRTY | T_YET_TOUPDATE;
}
void Transform::LocalScaleMultiply(float x_, float y_, float z_) {
	localScale.x *= x_;
	localScale.y *= y_;
	localScale.z *= z_;
	flags |= T_DIRTY | T_YET_TOUPDATE;
}
void Transform::LocalScaleMultiply(const ddd::Vector3& scaling_) {
	localScale.x *= scaling_.x;
	localScale.y *= scaling_.y;
	localScale.z *= scaling_.z;
	flags |= T_DIRTY | T_YET_TOUPDATE;
}

//______________________________________________________________________ getters
Transform Transform::GetConcatTransform() const
{
	if (parent)
	{
		return ConcatLocalVQS(parent->GetConcatTransform(), *this);
	}
	return *this;
}

Transform Transform::GetInverse() const {
	const ddd::Quaternion& invQuaternion = rotation.GetInverted();
	return Transform(invQuaternion * (-position), invQuaternion, ddd::Vector3::One);
}

const ddd::Matrix44& Transform::GetMatrix() {
	
	//if flag is dirty, concat the latest matrix
	if (flags & T_DIRTY) 
	{
		//should only be called by a transform with no parent
		worldMatrix = BuildTRS4x4(position, rotation, scale);
		//turn bit off
		flags &= ~T_DIRTY;
	}
	return worldMatrix;
}

ddd::Matrix44 Transform::GetLocalMatrix() const 
{ 
	return BuildTRS4x4(localPosition, localRotation, localScale);
}
const ddd::Matrix44&	Transform::GetWorldMatrix	() const { return worldMatrix; }
bool				Transform::HasUpdated		() const { return !(flags & T_DIRTY); }
bool				Transform::IsBone			() const { return (flags & T_ISBONE); }
bool				Transform::IsStatic			() const { return (flags & T_STATIC); }
ddd::Vector3			Transform::Forward			() const { return rotation.GetRotatedVector(facing); }
ddd::Vector3			Transform::Up				() const { return rotation.GetRotatedVector(ddd::Vector3::Vector3Y); }
ddd::Vector3			Transform::Right			() const { return Forward().Cross(ddd::Vector3::Vector3Y); } //rotation.GetRotatedVector(ddd::Vector3::Vector3X); }

// ______________________________________________________________________ etc function
void Transform::Attach(Transform* parent_) {
	//if parent is nullptr
	//if parent is itself
	//if parent is same
	if (!parent_ || parent_ == this || parent == parent_)
	{
#if defined(_DEBUG)
		Warn("Transform.cpp No Parent to be attached");
#endif
		return;
	}

	if (parent)
	{
		//delete child from old parent
		auto b = parent->child.begin();
		auto e = parent->child.end();
		std::vector<Transform*>::iterator itrToRemove = std::find(b, e, this);
		parent->child.erase(itrToRemove);
	}

	//assign to the new parent
	parent = parent_;
	ddd::Vector3 rec = (1.0f / parent->scale);
	ddd::Quaternion con = parent->rotation.GetConjugated();

	//localPosition = (con * (rec * position)) + (con * (rec * -parent->position)) ; //ddd::GaussJordanInverse(parent->GetMatrix()) * position;
	localPosition = ddd::GaussJordanInverse(parent->GetMatrix()) * position;
	localScale		= rec * scale;
	localRotation	= con * rotation;

	//attach child
	parent->child.push_back(this);

	SignalChildDirtyBit();
	flags |= T_DIRTY | T_YET_TOUPDATE;
}
void Transform::Detach() {
	if (!parent) return;

	position = ((parent->rotation * (parent->scale * localPosition))) + parent->position;
	rotation = parent->rotation * localRotation;
	scale	 = parent->scale * localScale;

	localPosition.SetZero();
	localScale		= ddd::Vector3::One;
	localRotation	= ddd::Quaternion{};

	//remove child
	auto b = parent->child.begin();
	auto e = parent->child.end();
	std::vector<Transform*>::iterator itrToRemove = std::find(b, e, this);
	parent->child.erase(itrToRemove);

	parent = nullptr;

	SignalChildDirtyBit();
	flags |= T_DIRTY;
}

void Transform::CameraLookAt(const Transform& target_)
{
	CameraLookAt(target_.position);
}
void Transform::CameraLookAt(const ddd::Vector3& target_position_)
{
	rotation = ddd::LookRotation(position - target_position_, Up(), facing);
	if (parent) {
		localRotation = rotation;
	}
	flags |= T_DIRTY;
}
void Transform::LookAt(const Transform& target_) {
	LookAt(target_.position);
}
void Transform::LookAt(const ddd::Vector3& target_) 
{
	rotation = ddd::LookRotation(target_ - position, ddd::Vector3::Vector3Y, facing);
	if (parent) 
	{
		//ddd::Quaternion con = parent->rotation.GetConjugated();
		//localRotation = con * rotation;

		localRotation = rotation;
	}
	flags |= T_DIRTY;
}
void Transform::LookAt(const ddd::Vector3& target_, const ddd::Vector3& facing_, const ddd::Vector3& up_)
{
	ddd::Quaternion getRot = ddd::LookRotation(target_ - position, up_, facing_);
	if (parent)
	{
		//Detach();
		//rotation = getRot;
		//Attach(parent);

		//ddd::Quaternion con = parent->rotation.GetConjugated();
		//localRotation = con * rotation;
		localRotation = rotation;
	}
	else
		rotation = getRot;

	flags |= T_DIRTY;
}
void Transform::Reset() {
	if (parent) 
	{
		localPosition	= ddd::Vector3{};
		localScale		= ddd::Vector3::One;
		localRotation	= ddd::Quaternion{};
		flags |= T_DIRTY | T_YET_TOUPDATE;
	}
	else 
	{
		position	= ddd::Vector3{};
		scale		= ddd::Vector3::One;
		rotation	= ddd::Quaternion{};
		worldMatrix.SetIdentity();
		flags |= T_DIRTY;
	}
}
void Transform::ResetFlag() 
{
	flags &= ~T_YET_TOUPDATE;
	
	if (parent) 
	{
		ddd::Vector3 rec = (1.0f / parent->scale);
		ddd::Quaternion con = parent->rotation.GetConjugated();

		localPosition	= ddd::GaussJordanInverse(parent->GetMatrix()) * position;
		//localPosition	= (con * (rec * position)) + (con * (rec * -parent->position)); //ddd::GaussJordanInverse(parent->GetMatrix()) * position;
		localScale		= rec * scale;
		localRotation	= con * rotation;

		SignalChildDirtyBit();
	}
}
void Transform::SetUpdateFlag()
{
	flags |= T_DIRTY | T_YET_TOUPDATE;
}

void Transform::RotateTowards(const Transform& target, float rate)
{
	RotateTowards(target.position, rate);
}
void Transform::RotateTowards(const ddd::Vector3& target, float rate)
{
	if (parent)
	{
		auto targetPos = target;

		auto tRot = ddd::LookRotation(targetPos - localPosition, ddd::Vector3::Vector3Y, Forward());

		auto dot = localRotation.Dot(tRot);

		if (std::abs(dot) > 1.f - EPSILON)
			dot = 0.f;
		else
			dot = TO_DEG(acos(std::min(abs(dot), 1.f)) * 2.f);

		if (dot == 0.f)
			SetLocalRotation(tRot);
		else
			SetLocalRotation(ddd::Slerp(localRotation, tRot, std::min(1.f, rate / dot)));
	}
	else
	{
		auto targetPos = target;

		auto tRot = ddd::LookRotation(targetPos - position, ddd::Vector3::Vector3Y, Forward());

		auto dot = rotation.Dot(tRot);

		if (std::abs(dot) > 1.f - EPSILON)
			dot = 0.f;
		else
			dot = TO_DEG(acos(std::min(abs(dot), 1.f)) * 2.f);

		if (dot == 0.f)
			SetRotation(tRot);
		else
			SetRotation(ddd::Slerp(rotation, tRot, std::min(1.f, rate / dot)));
	}
}
void Transform::RotateTowardsIgnoreHeight(const Transform & target, float rate)
{
	RotateTowardsIgnoreHeight(target.position, rate);
}
void Transform::RotateTowardsIgnoreHeight(const ddd::Vector3 & target, float rate)
{
	auto targetPos = target;
	targetPos.y = position.y;

	auto tRot = ddd::LookRotation(targetPos - position, ddd::Vector3::Vector3Y, Forward());

	auto dot = rotation.Dot(tRot);

	if (std::abs(dot) > 1.f - EPSILON)
		dot = 0.f;
	else
		dot = TO_DEG(acos(std::min(abs(dot), 1.f)) * 2.f);

	if (dot == 0.f)
		SetRotation(tRot);
	else
		SetRotation(ddd::Slerp(rotation, tRot, std::min(1.f, rate / dot)));
}
void Transform::Slerp(const ddd::Quaternion& q, float deltatime_) {
	rotation = ddd::Slerp(rotation, q, deltatime_);
	flags |= T_DIRTY;
}

void Transform::ForceUpdate()
{
	if (!parent)
		return;

	//if parent have yet to update, update upwards
	if ((parent->flags & T_YET_TOUPDATE))
		parent->Update();

	//VQS implmentation, update using latest value
	position = ((parent->rotation * (parent->scale * localPosition))) + parent->position;
	rotation = parent->rotation * localRotation;
	scale	 = parent->scale * localScale;

	//updated, reset flag
	//concat matrix
	worldMatrix = BuildTRS4x4(position, rotation, scale);
	flags &= ~T_DIRTY;			//reset dirty bit
	flags &= ~T_YET_TOUPDATE;	//reset T_YET_TOUPDATE bit
}
void Transform::Update() 
{
	//if is static
	if ((flags & T_STATIC))
	{
		flags &= ~T_DIRTY;			//reset dirty bit
		flags &= ~T_YET_TOUPDATE;	//reset T_YET_TOUPDATE bit
		return;
	}
	
	//if no parent 
	if (!parent)
	{
		//but flag bit is dirty
		//signal all child to dirty bit 
		if ((flags & T_DIRTY))
			SignalChildDirtyBit();
		return;
	}

	//reaching here means there is a parent
	if( (flags & T_DIRTY) || (flags & T_YET_TOUPDATE) )
	{
		//signal all child to dirty bit 
		//Update
		SignalChildDirtyBit();	
		ForceUpdate();
	}
}

ddd::Vector3 Transform::GetWorldPosition() const {
	if (parent)
		return ((parent->GetWorldRotation() * (parent->GetWorldScale() * localPosition)) ) + parent->GetWorldPosition();
	return position;
}
ddd::Quaternion Transform::GetWorldRotation() const {
	if (parent) 
		return parent->GetWorldRotation() * localRotation;
	return rotation;
}
ddd::Vector3 Transform::GetWorldScale() const {
	if (parent) 
		return parent->GetWorldScale() * localScale;
	return scale;
}


void Transform::dump() const {
	ddd::Vector3 eular = ddd::ToEularDegree(rotation);
	ddd::Vector3 localEular = ddd::ToEularDegree(localRotation);
	printf("worldT: %15.6f %15.6f %15.6f \nworldR: %15.6f %15.6f %15.6f \n\
worldS: %15.6f %15.6f %15.6f \n\
localT: %15.6f %15.6f %15.6f \n\
localR: %15.6f %15.6f %15.6f \n\
localS: %15.6f %15.6f %15.6f \n\n"
		, position.x, position.y, position.z
		, eular.x, eular.y, eular.z
		, scale.x, scale.y, scale.z
		, localPosition.x, localPosition.y, localPosition.z
		, localEular.x, localEular.y, localEular.z
		, localScale.x, localScale.y, localScale.z
	);
}

void Transform::SignalChildDirtyBit()
{
	for (auto& elem : child)
	{
		elem->flags |= T_YET_TOUPDATE;
		elem->SignalChildDirtyBit();
	}
}

#ifdef TINYXML2_EXPORT
// ____________________________________________________________ serial
void Transform::Serial(FXMLDocument* doc, FXMLNode* root){
	FXMLElement* pElem = doc->NewElement(IS_TRANSFORM);

	if (parent) 
	{
		position = ((parent->rotation * (parent->scale * localPosition))) + parent->position;
		rotation = parent->rotation * localRotation;
		scale = parent->scale * localScale;
	}

	FXMLElement* pSubElem = doc->NewElement("position");
	pSubElem->SetAttribute("x", position.x);
	pSubElem->SetAttribute("y", position.y);
	pSubElem->SetAttribute("z", position.z);
	pElem->InsertEndChild(pSubElem);

	pSubElem = doc->NewElement("scale");
	pSubElem->SetAttribute("x", scale.x);
	pSubElem->SetAttribute("y", scale.y);
	pSubElem->SetAttribute("z", scale.z);
	pElem->InsertEndChild(pSubElem);
	
	ddd::Vector3 getEuler = rotation.ToEularDegree();
	pSubElem = doc->NewElement("rotation");
	pSubElem->SetAttribute("x", getEuler.x);
	pSubElem->SetAttribute("y", getEuler.y);
	pSubElem->SetAttribute("z", getEuler.z);
	pElem->InsertEndChild(pSubElem);

	pSubElem = doc->NewElement("misc");
	pSubElem->SetAttribute("isStatic", (flags & T_STATIC));
	pSubElem->SetAttribute("isBone", (flags & T_ISBONE));
	pElem->InsertEndChild(pSubElem);

	root->InsertEndChild(pElem);
}
void Transform::Unserial(FXMLElement* pElem){
	FXMLElement* pSubElem = pElem->FirstChildElement("position");
	position.x = pSubElem->FloatAttribute("x");
	position.y = pSubElem->FloatAttribute("y");
	position.z = pSubElem->FloatAttribute("z");

	pSubElem = pSubElem->NextSiblingElement();
	scale.x = pSubElem->FloatAttribute("x");
	scale.y = pSubElem->FloatAttribute("y");
	scale.z = pSubElem->FloatAttribute("z");

	ddd::Vector3 getEuler;
	pSubElem = pSubElem->NextSiblingElement();
	getEuler.x = pSubElem->FloatAttribute("x");
	getEuler.y = pSubElem->FloatAttribute("y");
	getEuler.z = pSubElem->FloatAttribute("z");
	rotation = ddd::ToQuaternion(getEuler);

	pSubElem = pSubElem->NextSiblingElement();

	bool getBool = pSubElem->BoolAttribute("isStatic");
	SetStatic(getBool);
	getBool = pSubElem->BoolAttribute("isBone");
	SetAsBoneObject(getBool);
}

#endif

// ____________________________________________________________ friend
Transform ConcatVQS(const Transform& t2_, const Transform& t1_) {
	return Transform{
		t2_.rotation * (t2_.scale * t1_.position) + t2_.position,
		t2_.rotation * t1_.rotation,
		t2_.scale * t1_.scale
	};
}
Transform ConcatLocalVQS(const Transform& t2_, const Transform& t1_) {
	return Transform{
		t2_.rotation * (t2_.scale * t1_.localPosition) + t2_.position,
		t2_.rotation * t1_.localRotation,
		t2_.scale * t1_.localScale
	};
	//VQM
	//ddd::Quaternion q1{ t1_.localRotation };
	//ddd::Quaternion q1c{ t1_.localRotation.GetConjugated() };
	//return Transform{
	//	t2_.rotation * (t2_.scale * t1_.localPosition) * t2_.rotation.GetConjugated(),
	//	t2_.rotation * q1,
	//	(q1c * t2_.scale) * (q1 * t1_.localScale)
	//};
}

// ____________________________________________________________ extern function
Transform InterpolateTransforms(const Transform& oldTransform,
	const Transform& newTransform,
	float factor) {

	ddd::Vector3 interPosition = oldTransform.position * (float(1.0) - factor) +
		newTransform.position * factor;
	ddd::Quaternion interOrientation = ddd::Slerp(oldTransform.rotation,
		newTransform.rotation, factor);
	return Transform(interPosition, interOrientation, ddd::Vector3::One);
}
void RotateTowards(Transform& transform_, const Transform& target, float rate)
{
	transform_.RotateTowards(target, rate);
}
void RotateTowards(Transform& transform_, const ddd::Vector3& target, float rate)
{
	transform_.RotateTowards(target, rate);
}

} // namespace ddd
