#pragma once
#ifndef _V_ARTICULATIONPLACE_H_
#define _V_ARTICULATIONPLACE_H_

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VArticulationPlaceCategory
    //----------------------------------------------------------------------------------------------------
    enum class VArticulationPlaceCategory
    {
        Active,
        Passive
        
        // ArticulatoryPerspective,
        // PerceptualClassification
    };
    
    // VArticulationPlaceActive
    //----------------------------------------------------------------------------------------------------
    enum class VArticulationPlaceActive
    {
        LowerLip,
        TongueBlade,
        TongueTip,
        TongueUnderside,
        TongueBody,
        TongueRoot,
        Larynx
    };
    
    // VArticulationPlacePassive
    //----------------------------------------------------------------------------------------------------
    enum class VArticulationPlacePassive
    {
        UpperLip,
        UpperTeeth,
        AlveolarRidge,
        BackOfAlveolarRidge,
        HardPalate,
        SoftPalate,
        Uvula,
        Pharynx,
        Epiglottis,
        Glottis
    };
    
    // VArticulationPlaceMajorClass
    //----------------------------------------------------------------------------------------------------
    // Front: Labial, Coronal
    // Back: Guttural
    //----------------------------------------------------------------------------------------------------
    // enum class VArticulationPlaceMajorClass
    // {
    //     Labial = 0,
    //     Coronal,
    //     Guttural,
    // };
    
    // VArticulationPlaceCombination
    //----------------------------------------------------------------------------------------------------
    // The place of articulation of a consonant is the point of contact where an obstruction occurs in the vocal tract between an articulatory gesture and a passive location.
    //----------------------------------------------------------------------------------------------------
    enum class VArticulationPlaceCombination
    {
        Bilabial,
        Labiodental,
        
        Linguolabial,
        Interdental,
        DentiAlveolar,
        LaminalAlveolar,
        PalatoAlveolar,
        
        Dental,
        ApicoAlveolar,
        ApicalRetroflex,
        
        Retroflex,
        
        AlveoloPalatal,
        Palatal,
        Velar,
        Uvular,
        
        Pharyngeal,
        
        EpiglottoPharyngeal,
        Epiglottal,
        Glottal
    };
    
    // VArticulationPlace
    //----------------------------------------------------------------------------------------------------
    
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VArticulationPlaceTest();
}

#endif
