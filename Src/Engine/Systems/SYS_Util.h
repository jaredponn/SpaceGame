#pragma once

// -----------------------------------------
//    macros to help map over componenets
// -----------------------------------------

#define TRANSFORM_MANAGER_WITH(                                                     \
	transformdata,	/** <..>Manager* ... data to be transformed*/         \
	transformdata_prefix, /** prefix of the transformdata type  for the         \
				 manager and vector. should be the same as the      \
				 type*/                                             \
	func,		      /** function that follows the format of:              \
				 FUNC(transformdata_prefix*, constdata_prefix*) */  \
	constdata,	    /** the other data used to transform the data*/       \
	constdata_prefix /**the other data's prefix*/)                              \
	{                                                                           \
		/** getting the transform data's vector, and itslength*/            \
		const struct transformdata_prefix##Vector                           \
			*transformdata##Data =                                      \
				transformdata_prefix##Manager_get_packed_data(      \
					transformdata);                             \
		const size_t transformdata##VecLength =                             \
			transformdata_prefix##Vector_size(                          \
				transformdata##Data);                               \
                                                                                    \
		/** temporary vars*/                                                \
		void *transformdata_prefix##Tmp, *constdata_prefix##Tmp;            \
                                                                                    \
		for (size_t i = 0; i < transformdata##VecLength; ++i) {             \
			transformdata_prefix##Tmp =                                 \
				transformdata_prefix##Vector_get_p(                 \
					transformdata##Data, i);                    \
			constdata_prefix##Tmp = constdata_prefix##Manager_get_p_at( \
				(struct constdata_prefix##Manager *)constdata,      \
				transformdata_prefix##Manager_get_index_from(       \
					transformdata, i));                         \
			/** checking if that data exists before applying the        \
			 * transform*/                                              \
			if (transformdata_prefix##Tmp != NULL                       \
			    && constdata_prefix##Tmp != NULL)                       \
				func(transformdata_prefix##Tmp,                     \
				     constdata_prefix##Tmp);                        \
		}                                                                   \
	}
