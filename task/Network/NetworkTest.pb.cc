// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: NetworkTest.proto

#include "NetworkTest.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
namespace NetworkTest {
class RegisterDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<Register> _instance;
} _Register_default_instance_;
class QueryDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<Query> _instance;
} _Query_default_instance_;
class ResultDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<Result> _instance;
} _Result_default_instance_;
}  // namespace NetworkTest
static void InitDefaultsscc_info_Query_NetworkTest_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::NetworkTest::_Query_default_instance_;
    new (ptr) ::NetworkTest::Query();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::NetworkTest::Query::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_Query_NetworkTest_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_Query_NetworkTest_2eproto}, {}};

static void InitDefaultsscc_info_Register_NetworkTest_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::NetworkTest::_Register_default_instance_;
    new (ptr) ::NetworkTest::Register();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::NetworkTest::Register::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_Register_NetworkTest_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_Register_NetworkTest_2eproto}, {}};

static void InitDefaultsscc_info_Result_NetworkTest_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::NetworkTest::_Result_default_instance_;
    new (ptr) ::NetworkTest::Result();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::NetworkTest::Result::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_Result_NetworkTest_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_Result_NetworkTest_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_NetworkTest_2eproto[3];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_NetworkTest_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_NetworkTest_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_NetworkTest_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::NetworkTest::Register, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::NetworkTest::Register, content_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::NetworkTest::Query, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::NetworkTest::Query, id_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::NetworkTest::Result, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::NetworkTest::Result, id_),
  PROTOBUF_FIELD_OFFSET(::NetworkTest::Result, reason_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::NetworkTest::Register)},
  { 6, -1, sizeof(::NetworkTest::Query)},
  { 12, -1, sizeof(::NetworkTest::Result)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::NetworkTest::_Register_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::NetworkTest::_Query_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::NetworkTest::_Result_default_instance_),
};

const char descriptor_table_protodef_NetworkTest_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\021NetworkTest.proto\022\013NetworkTest\"\033\n\010Regi"
  "ster\022\017\n\007content\030\002 \001(\014\"\023\n\005Query\022\n\n\002id\030\001 \001"
  "(\r\"$\n\006Result\022\n\n\002id\030\001 \001(\r\022\016\n\006reason\030\002 \001(\r"
  "2~\n\002NT\022>\n\016AnswerRegister\022\025.NetworkTest.R"
  "egister\032\023.NetworkTest.Result\"\000\0228\n\013Result"
  "Query\022\022.NetworkTest.Query\032\023.NetworkTest."
  "Result\"\000b\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_NetworkTest_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_NetworkTest_2eproto_sccs[3] = {
  &scc_info_Query_NetworkTest_2eproto.base,
  &scc_info_Register_NetworkTest_2eproto.base,
  &scc_info_Result_NetworkTest_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_NetworkTest_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_NetworkTest_2eproto = {
  false, false, descriptor_table_protodef_NetworkTest_2eproto, "NetworkTest.proto", 256,
  &descriptor_table_NetworkTest_2eproto_once, descriptor_table_NetworkTest_2eproto_sccs, descriptor_table_NetworkTest_2eproto_deps, 3, 0,
  schemas, file_default_instances, TableStruct_NetworkTest_2eproto::offsets,
  file_level_metadata_NetworkTest_2eproto, 3, file_level_enum_descriptors_NetworkTest_2eproto, file_level_service_descriptors_NetworkTest_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_NetworkTest_2eproto = (static_cast<void>(::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_NetworkTest_2eproto)), true);
namespace NetworkTest {

// ===================================================================

void Register::InitAsDefaultInstance() {
}
class Register::_Internal {
 public:
};

Register::Register(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:NetworkTest.Register)
}
Register::Register(const Register& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  content_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_content().empty()) {
    content_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from._internal_content(),
      GetArena());
  }
  // @@protoc_insertion_point(copy_constructor:NetworkTest.Register)
}

void Register::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_Register_NetworkTest_2eproto.base);
  content_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

Register::~Register() {
  // @@protoc_insertion_point(destructor:NetworkTest.Register)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void Register::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  content_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void Register::ArenaDtor(void* object) {
  Register* _this = reinterpret_cast< Register* >(object);
  (void)_this;
}
void Register::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Register::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const Register& Register::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_Register_NetworkTest_2eproto.base);
  return *internal_default_instance();
}


void Register::Clear() {
// @@protoc_insertion_point(message_clear_start:NetworkTest.Register)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  content_.ClearToEmpty(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Register::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  ::PROTOBUF_NAMESPACE_ID::Arena* arena = GetArena(); (void)arena;
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // bytes content = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          auto str = _internal_mutable_content();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* Register::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:NetworkTest.Register)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // bytes content = 2;
  if (this->content().size() > 0) {
    target = stream->WriteBytesMaybeAliased(
        2, this->_internal_content(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:NetworkTest.Register)
  return target;
}

size_t Register::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:NetworkTest.Register)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // bytes content = 2;
  if (this->content().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_content());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Register::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:NetworkTest.Register)
  GOOGLE_DCHECK_NE(&from, this);
  const Register* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<Register>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:NetworkTest.Register)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:NetworkTest.Register)
    MergeFrom(*source);
  }
}

void Register::MergeFrom(const Register& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:NetworkTest.Register)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.content().size() > 0) {
    _internal_set_content(from._internal_content());
  }
}

void Register::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:NetworkTest.Register)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Register::CopyFrom(const Register& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:NetworkTest.Register)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Register::IsInitialized() const {
  return true;
}

void Register::InternalSwap(Register* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  content_.Swap(&other->content_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}

::PROTOBUF_NAMESPACE_ID::Metadata Register::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

void Query::InitAsDefaultInstance() {
}
class Query::_Internal {
 public:
};

Query::Query(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:NetworkTest.Query)
}
Query::Query(const Query& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  id_ = from.id_;
  // @@protoc_insertion_point(copy_constructor:NetworkTest.Query)
}

void Query::SharedCtor() {
  id_ = 0u;
}

Query::~Query() {
  // @@protoc_insertion_point(destructor:NetworkTest.Query)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void Query::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
}

void Query::ArenaDtor(void* object) {
  Query* _this = reinterpret_cast< Query* >(object);
  (void)_this;
}
void Query::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Query::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const Query& Query::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_Query_NetworkTest_2eproto.base);
  return *internal_default_instance();
}


void Query::Clear() {
// @@protoc_insertion_point(message_clear_start:NetworkTest.Query)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  id_ = 0u;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Query::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  ::PROTOBUF_NAMESPACE_ID::Arena* arena = GetArena(); (void)arena;
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // uint32 id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* Query::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:NetworkTest.Query)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // uint32 id = 1;
  if (this->id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(1, this->_internal_id(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:NetworkTest.Query)
  return target;
}

size_t Query::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:NetworkTest.Query)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // uint32 id = 1;
  if (this->id() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
        this->_internal_id());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Query::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:NetworkTest.Query)
  GOOGLE_DCHECK_NE(&from, this);
  const Query* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<Query>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:NetworkTest.Query)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:NetworkTest.Query)
    MergeFrom(*source);
  }
}

void Query::MergeFrom(const Query& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:NetworkTest.Query)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.id() != 0) {
    _internal_set_id(from._internal_id());
  }
}

void Query::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:NetworkTest.Query)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Query::CopyFrom(const Query& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:NetworkTest.Query)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Query::IsInitialized() const {
  return true;
}

void Query::InternalSwap(Query* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  swap(id_, other->id_);
}

::PROTOBUF_NAMESPACE_ID::Metadata Query::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

void Result::InitAsDefaultInstance() {
}
class Result::_Internal {
 public:
};

Result::Result(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:NetworkTest.Result)
}
Result::Result(const Result& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&id_, &from.id_,
    static_cast<size_t>(reinterpret_cast<char*>(&reason_) -
    reinterpret_cast<char*>(&id_)) + sizeof(reason_));
  // @@protoc_insertion_point(copy_constructor:NetworkTest.Result)
}

void Result::SharedCtor() {
  ::memset(&id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&reason_) -
      reinterpret_cast<char*>(&id_)) + sizeof(reason_));
}

Result::~Result() {
  // @@protoc_insertion_point(destructor:NetworkTest.Result)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void Result::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
}

void Result::ArenaDtor(void* object) {
  Result* _this = reinterpret_cast< Result* >(object);
  (void)_this;
}
void Result::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Result::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const Result& Result::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_Result_NetworkTest_2eproto.base);
  return *internal_default_instance();
}


void Result::Clear() {
// @@protoc_insertion_point(message_clear_start:NetworkTest.Result)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&reason_) -
      reinterpret_cast<char*>(&id_)) + sizeof(reason_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Result::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  ::PROTOBUF_NAMESPACE_ID::Arena* arena = GetArena(); (void)arena;
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // uint32 id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // uint32 reason = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          reason_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* Result::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:NetworkTest.Result)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // uint32 id = 1;
  if (this->id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(1, this->_internal_id(), target);
  }

  // uint32 reason = 2;
  if (this->reason() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(2, this->_internal_reason(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:NetworkTest.Result)
  return target;
}

size_t Result::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:NetworkTest.Result)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // uint32 id = 1;
  if (this->id() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
        this->_internal_id());
  }

  // uint32 reason = 2;
  if (this->reason() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
        this->_internal_reason());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Result::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:NetworkTest.Result)
  GOOGLE_DCHECK_NE(&from, this);
  const Result* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<Result>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:NetworkTest.Result)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:NetworkTest.Result)
    MergeFrom(*source);
  }
}

void Result::MergeFrom(const Result& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:NetworkTest.Result)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.id() != 0) {
    _internal_set_id(from._internal_id());
  }
  if (from.reason() != 0) {
    _internal_set_reason(from._internal_reason());
  }
}

void Result::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:NetworkTest.Result)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Result::CopyFrom(const Result& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:NetworkTest.Result)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Result::IsInitialized() const {
  return true;
}

void Result::InternalSwap(Result* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(Result, reason_)
      + sizeof(Result::reason_)
      - PROTOBUF_FIELD_OFFSET(Result, id_)>(
          reinterpret_cast<char*>(&id_),
          reinterpret_cast<char*>(&other->id_));
}

::PROTOBUF_NAMESPACE_ID::Metadata Result::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace NetworkTest
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::NetworkTest::Register* Arena::CreateMaybeMessage< ::NetworkTest::Register >(Arena* arena) {
  return Arena::CreateMessageInternal< ::NetworkTest::Register >(arena);
}
template<> PROTOBUF_NOINLINE ::NetworkTest::Query* Arena::CreateMaybeMessage< ::NetworkTest::Query >(Arena* arena) {
  return Arena::CreateMessageInternal< ::NetworkTest::Query >(arena);
}
template<> PROTOBUF_NOINLINE ::NetworkTest::Result* Arena::CreateMaybeMessage< ::NetworkTest::Result >(Arena* arena) {
  return Arena::CreateMessageInternal< ::NetworkTest::Result >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
